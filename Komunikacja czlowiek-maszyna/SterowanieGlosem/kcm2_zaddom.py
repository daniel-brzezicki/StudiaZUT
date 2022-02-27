#Daniel Brzezicki KCM bd46477

import pyaudio
import speech_recognition as sr
import pyautogui
from selenium import webdriver
from selenium.webdriver.common.keys import Keys

def get_audio(lang):
 r = sr.Recognizer()
 r.energy_threshold = 800
 with sr.Microphone() as source:
    print("Powiedz komendę. Nasłuchuję...")
    audio = r.listen(source)
    said = ""
    try:
        said = r.recognize_google(audio, language = lang)
        print(said)
    except Exception as e:
        print("Exception: " + str(e))
 return said


def get_number_from_audio():
    text = get_audio("pl_PL")
    if(text.isnumeric()):
        ilosc = int(text)
    else:
        ilosc=0

    return ilosc


def command(text):
    speed=0.5
    t = text.lower()

    match t:
        case 'otwórz':
            #Należy podać ścieżkę do geckodriver.exe!!!
            browser = webdriver.Firefox(executable_path="C:/Users/danie/source/repos/kcmprogram/geckodriver.exe")
            browser.get("https://kleki.com")
        case 'kliknij':
            pyautogui.leftClick()
        case 'trzymaj':
            pyautogui.mouseDown()
        case 'puść':
            pyautogui.mouseUp()
        case 'góra':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x,pyautogui.position().y-ilosc, speed, pyautogui.easeOutQuad) 
        case 'dół':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x,pyautogui.position().y+ilosc, speed, pyautogui.easeOutQuad) 
        case 'prawo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x+ilosc,pyautogui.position().y, speed, pyautogui.easeOutQuad) 
        case 'lewo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x-ilosc,pyautogui.position().y, speed, pyautogui.easeOutQuad)
        case 'lewo góra':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x-ilosc,pyautogui.position().y-ilosc, speed, pyautogui.easeOutQuad) 
        case 'góra lewo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x-ilosc,pyautogui.position().y-ilosc, speed, pyautogui.easeOutQuad)
        case 'prawo góra':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x+ilosc,pyautogui.position().y-ilosc, speed, pyautogui.easeOutQuad) 
        case 'góra prawo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x+ilosc,pyautogui.position().y-ilosc, speed, pyautogui.easeOutQuad)
        case 'lewo dół':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x-ilosc,pyautogui.position().y+ilosc, speed, pyautogui.easeOutQuad) 
        case 'dół lewo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x-ilosc,pyautogui.position().y+ilosc, speed, pyautogui.easeOutQuad)
        case 'prawo dół':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x+ilosc,pyautogui.position().y+ilosc, speed, pyautogui.easeOutQuad) 
        case 'dół prawo':
            ilosc = get_number_from_audio()
            pyautogui.moveTo(pyautogui.position().x+ilosc,pyautogui.position().y+ilosc, speed, pyautogui.easeOutQuad)

            
     

while(1):
    text = get_audio("pl_PL")
    command(text)
