from googletrans import Translator
import pyaudio
import speech_recognition as sr
import os
import playsound
from gtts import gTTS

def get_audio(lang):
 r = sr.Recognizer()
 # większy threshold jeśli mikrofon szumi
 r.energy_threshold = 800
 with sr.Microphone() as source:
    print("Powiedz zdanie, które chcesz przetłumaczyć. Nasłuchuję...")
    audio = r.listen(source)
    said = ""
    try:
        said = r.recognize_google(audio, language = lang)
        print(said)
    except Exception as e:
        print("Exception: " + str(e))
 return said

def translate(text,sourceLang, destLang):
    translator = Translator()
    translated = translator.translate(text, src=sourceLang, dest=destLang)
    print(translated.text)
    return translated.text, destLang

def speak(text,lang):
    tts = gTTS(text=text, lang=lang)
    filename = "voiceTranslated.mp3"
    tts.save(filename)
    playsound.playsound(filename)
    os.remove(filename)


translateTo = 'en'
text = get_audio("pl_PL")
translated, destLang = translate(text, 'pl', translateTo)
speak(translated, destLang)



