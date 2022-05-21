import numpy as np
import matplotlib.pyplot as plt
import scipy.fftpack
import cv2
from tqdm import tqdm

RGB2YCrCb = lambda RGB: cv2.cvtColor(RGB, cv2.COLOR_RGB2YCrCb).astype(int)
YCrCb2RGB = lambda YCrCb: cv2.cvtColor(YCrCb.astype(np.uint8), cv2.COLOR_YCrCb2RGB)


def colorFit(colors, palette):
    return palette[np.argmin(np.sum(np.abs(palette - colors), axis=1))]


def checkImage(sourceIm):
    if (sourceIm.dtype == np.uint8):
        image = sourceIm.copy() / 255
    else:
        image = sourceIm.copy()
    return image


def quantize(img, palette):
    image = checkImage(img)

    height, width = image.shape[:2]

    for y in tqdm(range(width)):
        for x in range(height):
            image[x, y] = colorFit(image[x, y], palette)

    return image


def png2jpg(png):
    return png[:, :, :3]


def reduce_chroma(YCrCb, params):
    J, a, b = list(map(int, params.split(':')))
    Y = YCrCb[:, :, 0]
    Cr = YCrCb[:, :, 1]
    Cb = YCrCb[:, :, 2]

    Cr_blocks = Cr.reshape(Cr.shape[0] // 2, -1, 2, J).transpose([0, 2, 1, 3])
    Cb_blocks = Cb.reshape(Cb.shape[0] // 2, -1, 2, J).transpose([0, 2, 1, 3])

    pom = 0
    for idx_block_row, block_row in enumerate(Cr_blocks):
        for idx_block, block in enumerate(block_row):
            for idx_row, row in enumerate(block):
                for idx_col, val in enumerate(row):
                    if idx_row == 0:
                        if idx_col % (J // a) == 0:
                            pom = val
                    else:
                        if idx_col % (J // b) == 0:
                            pom = val

                    Cr_blocks[idx_block_row, idx_block, idx_row, idx_col] = pom

    pom = 0
    for idx_block_row, block_row in enumerate(Cb_blocks):
        for idx_block, block in enumerate(block_row):
            for idx_row, row in enumerate(block):
                for idx_col, val in enumerate(row):
                    if idx_row == 0:
                        if idx_col % (J // a) == 0:
                            pom = val
                    else:
                        if idx_col % (J // b) == 0:
                            pom = val

                    Cb_blocks[idx_block_row, idx_block, idx_row, idx_col] = pom

    Cr_reduced = Cr_blocks.transpose([0, 2, 1, 3]).reshape(Cr.shape)
    Cb_reduced = Cb_blocks.transpose([0, 2, 1, 3]).reshape(Cr.shape)

    return np.dstack([Y, Cr_reduced, Cb_reduced]).astype(np.uint8)


dct2 = lambda a: scipy.fftpack.dct(scipy.fftpack.dct(a.astype(float), axis=0, norm='ortho'), axis=1, norm='ortho')
idct2 = lambda a: scipy.fftpack.idct(scipy.fftpack.idct(a.astype(float), axis=0, norm='ortho'), axis=1, norm='ortho')


def zigzag(A):
    template = n = np.array([
        [0, 1, 5, 6, 14, 15, 27, 28],
        [2, 4, 7, 13, 16, 26, 29, 42],
        [3, 8, 12, 17, 25, 30, 41, 43],
        [9, 11, 18, 24, 31, 40, 44, 53],
        [10, 19, 23, 32, 39, 45, 52, 54],
        [20, 22, 33, 38, 46, 51, 55, 60],
        [21, 34, 37, 47, 50, 56, 59, 61],
        [35, 36, 48, 49, 57, 58, 62, 63],
    ])
    if len(A.shape) == 1:
        B = np.zeros((8, 8))
        for r in range(0, 8):
            for c in range(0, 8):
                B[r, c] = A[template[r, c]]
    else:
        B = np.zeros((64,))
        for r in range(0, 8):
            for c in range(0, 8):
                B[template[r, c]] = A[r, c]
    return B


paletts = {'RGB1Byte': np.array([
    [0., 0., 0.],
    [0., 0., 1.],
    [0., 1., 0.],
    [0., 1., 1.],
    [1., 0., 0.],
    [1., 0., 1.],
    [1., 1., 0.],
    [1., 1., 1.]
]),
    'RGB2Byte': np.array([
        [0, 0, 0],
        [0, 1, 1],
        [0, 0, 1],
        [1, 0, 1],
        [0, 0.5, 0],
        [0.5, 0.5, 0.5],
        [0, 1, 0],
        [0.5, 0, 0],
        [0, 0, 0.5],
        [0.5, 0.5, 0],
        [0.5, 0, 0.5],
        [1, 0, 0],
        [0.75, 0.75, 0.75],
        [0, 0.5, 0.5],
        [1, 1, 1],
        [1, 1, 0]
    ])
}


def test_image(RGB):
    YCrCb = RGB2YCrCb(RGB)
    chromed = reduce_chroma(YCrCb, '64:1:1')
    return YCrCb2RGB(chromed)


def Test(images, palettes, flags):
    for img in images:
        image = plt.imread(images[img])
        plt.title('Original image')
        plt.imshow(image)
        plt.savefig(img + '/orig_' + img)
        plt.show()

        for pal in palettes:
            palette = palettes[pal]

            if flags['quantize']:
                im = (plt.imread(images[img])[:552, :832, :3] * 256).astype(np.uint8)
                reduced = test_image(im)
                q = quantize(reduced, palette)
                plt.title('Quantize')
                plt.imshow(q)
                plt.savefig(img + '/' + img + '_' + pal + '_quantize_6411')
                plt.show()

            if flags['reduce']:
                im = (plt.imread(images[img])[:552, :832, :3] * 256).astype(np.uint8)
                plt.title('Before reducing')
                plt.imshow(im)
                plt.savefig(img + '/' + '_before')
                plt.show()

                reduced = test_image(im)
                plt.title('After reducing')
                plt.imshow(reduced)
                plt.savefig(img + '/' + '_6411')
                plt.show()


if __name__ == '__main__':
    flags = {
        'quantize': True,
        'reduce': True
    }

    images = {
        'test': 'test.png',
        'piesek1': 'piesek1.png',
        'piesek2': 'pies2.png'
    }

    Test(images, paletts, flags)
