import math
from tracemalloc import stop
from sympy import *
import numpy as np
import sys
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import (
    QApplication,
    QCheckBox,
    QComboBox,
    QDateEdit,
    QDateTimeEdit,
    QDial,
    QDialog,
    QDoubleSpinBox,
    QFontComboBox,
    QGridLayout,
    QLabel,
    QLCDNumber,
    QLineEdit,
    QMainWindow,
    QProgressBar,
    QPushButton,
    QRadioButton,
    QSlider,
    QSpinBox,
    QTimeEdit,
    QVBoxLayout,
    QHBoxLayout,
    QWidget,
) # see https://www.pythonguis.com/tutorials/pyqt-basic-widgets/

from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import matplotlib.pyplot as plt
import random
import win32api
from tkinter import filedialog
import re
import timeit
from matplotlib.animation import FuncAnimation, writers
import os

class Aproximare(QMainWindow):
    # constructor
    def __init__(self, parent=None):
        super(Aproximare, self).__init__(parent)
        #initializari
        self.n=0
        self.figure = plt.figure()
        self.canvas = FigureCanvas(self.figure)

        self.campFunctie = QLineEdit('exp(sin(x))')
        self.campN = QLineEdit('-')
        self.campA = QLineEdit('0')
        self.campB = QLineEdit('10')
        self.campX = QLineEdit('liniar')
        self.bern = QLineEdit('Aici se va afisa polinomul')

        layoutF = QHBoxLayout()
        layoutF.addWidget(QLabel('f = '))
        layoutF.addWidget(self.campFunctie)
        layoutF.addWidget(QLabel('n = '))
        layoutF.addWidget(self.campN)
        self.campN.setMaximumWidth(30)

        layoutAB = QGridLayout()#ca sa poata fii adaugate mesaje eroare text sub campuri
        layoutAB.addWidget(QLabel('a = '), 0, 0)
        layoutAB.addWidget(self.campA, 0 , 1)
        self.eroareA = QLabel("a trebuie sa fie mai mic ca b")
        layoutAB.addWidget(self.eroareA, 1, 1)
        #self.eroareA.setVisible(False)
        layoutAB.addWidget(QLabel('b = '), 0, 2)
        layoutAB.addWidget(self.campB, 0, 3)
        self.eroareB = QLabel("b trebuie sa fie mai mare ca a")
        #self.eroareB.setVisible(False)
        layoutAB.addWidget(self.eroareB, 1, 3)

        self.butonLiniar = QPushButton('Liniar')
        self.butonRandom = QPushButton('Random')
        self.butonTxt = QPushButton('Fisier')
        self.butonLiniar.setMaximumWidth(60)
        self.butonRandom.setMaximumWidth(60)
        self.butonTxt.setMaximumWidth(60)

        layoutX = QGridLayout()
        layoutX.addWidget(QLabel('x = '), 0, 0)
        layoutX.addWidget(self.campX, 0, 1)
        layoutX.addWidget(self.butonLiniar, 0, 2)
        layoutX.addWidget(self.butonRandom, 0, 3)
        layoutX.addWidget(self.butonTxt, 0, 4)
        layoutX.addWidget(QLabel("Se accepta doar numere rationale separate prin spatii"), 1, 1)


        self.butonUrmatorul = QPushButton('Urmatorul grad')
        self.butonFilm = QPushButton('Salveaza ca MP4')
        layoutButoane = QHBoxLayout()
        self.butonPlay = QPushButton('Play')
        layoutButoane.addWidget(self.butonPlay)
        self.butonStop = QPushButton('Stop')
        layoutButoane.addWidget(self.butonStop)
        self.butonReset = QPushButton('Reset')
        layoutButoane.addWidget(self.butonReset)

        layout = QVBoxLayout()

        layout.addLayout(layoutF)
        layout.addLayout(layoutAB)
        layout.addLayout(layoutX)
        layout.addWidget(self.canvas)
        layout.addWidget(self.bern)
        layout.addWidget(self.butonFilm)
        layout.addWidget(self.butonUrmatorul)
        layout.addLayout(layoutButoane)
        
        self.butonFilm.clicked.connect(self.film)
        self.butonUrmatorul.clicked.connect(self.next)
        self.butonPlay.clicked.connect(self.play)
        self.butonStop.clicked.connect(self.stop)
        self.butonReset.clicked.connect(self.reset)

        self.butonRandom.clicked.connect(self.random)
        self.butonLiniar.clicked.connect(self.liniar)
        self.butonTxt.clicked.connect(self.fisier)

        self.campN.textChanged.connect(self.modificare_n)

        self.campX.textChanged.connect(self.reset)
        self.campA.textChanged.connect(self.reset)
        self.campB.textChanged.connect(self.reset)
        self.campFunctie.textChanged.connect(self.reset)

        self.canvas.mpl_connect('button_press_event', self.click_canvas)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)

        self.show()

        fs = 'exp(sin(x))'
        x = Symbol('x')
        self.f = lambdify(x,fs)
        self.a=0
        self.b=10
        self.x_val = np.linspace(self.a, self.b, 100)
        self.t_val = (self.x_val-self.a)/(self.b-self.a) # x_val = t_val*(b-a)+a

        ax=self.figure.add_subplot()
        ax.scatter(self.x_val,self.f(self.x_val))

        self.timer = QtCore.QTimer()
        self.timer.setInterval(100)
        self.timer.timeout.connect(self.update_plot)

    def parsare_x(self):
        if len(self.campX.text()) == 0:
            win32api.MessageBox(0, 'Campul x e gol!', 'Eroare', 0x00001030) 
            raise Exception("Campul e gol")
        if self.campX.text() == "liniar":
            return np.linspace(self.a, self.b, 100)
        else:
            if self.campX.text() == "random":
                campXRandom = ""
                for i in range(10):
                    campXRandom+= (str(random.random() * (self.b - self.a) + self.a) + " ")
                self.campX.setText(campXRandom)
            ret_str = self.campX.text().split(" ")
            ret = []
            for curent in ret_str:
                try:
                    if len(curent) != 0:
                        ret.append(float(curent))
                except:
                    win32api.MessageBox(0, 'Campul x contine text sau alte simboluri! Folositi doar numere rationale, separate de simbolul punct!', 'Eroare', 0x00001030) 
                    raise Exception("Campul contine altceva in afara de numere")
            if len(ret) == 0:
                win32api.MessageBox(0, 'Campul contine doar spatii!', 'Eroare', 0x00001030) 
                raise Exception("Campul contine doar spatii")
            ret.sort()
            if(self.validare_x(np.array(ret))):
                return np.array(ret)
            else:
                raise Exception("x-ul este invalid")

    def actualizare(self) -> bool:
        if self.validare_a() and self.validare_b(): 
            fs = self.campFunctie.text()
            try:
                x = Symbol('x')
                self.f = lambdify(x,fs)
            except:
                return False
            self.a = float(self.campA.text())
            self.b = float(self.campB.text())
            try:
                self.x_val = self.parsare_x()
                self.t_val = (self.x_val-self.a)/(self.b-self.a) # x_val = t_val*(b-a)+a
            except:
                return False
        else:
            return False

        return True

    def modificare_n(self):
        if self.validare_n():
            if self.campN.text() == "-":
                self.n = 0
            else:
                self.n = int(self.campN.text())
        else:
            self.stop()#ne oprim la gradul 1028 deoarece altfel int-ul depaseste lungimea maxima in timpul calculului si primim exceptie

    def update_plot(self):
        self.figure.clear()
        ax=self.figure.add_subplot()
        ax.scatter(self.x_val,self.f(self.x_val))
        start = timeit.default_timer()
        self.campN.setText(str(self.n + 1))
        n=self.n
        f=self.f
        x_val=self.x_val
        t_val=self.t_val
        a=self.a
        b=self.b
        bern = np.zeros_like(self.x_val)
        polinom = "0"
        t="((x-"+str(self.a)+")/("+str(self.b-self.a)+"))"
        autoplaying = self.timer.isActive()
        if not autoplaying and self.n > 30:#polinomul de grad 30 poate dura si 15 secunde calcularea si simplificarea
            autoplaying = True
        for k in range(n+1):
            bern+=f((k/n)*(b-a)+a)*math.comb(n,k)*t_val**k*(1-t_val)**(n-k)
            if not autoplaying:
                polinom+="+"+str(f((k/n)*(b-a)+a)*math.comb(n,k))+"*"+t+"**" + str(k) + "*(1-"+t+")**("+str(n-k)+")"
        if not autoplaying:
            polinom="B(x)="+str(simplify(polinom))#consuma foarte mult procesor!
            self.bern.setText(polinom)
        else:
            self.bern.setText("Calcularea string-ului ar dura peste 15 secunde.")
        stop = timeit.default_timer()
        ax.plot(x_val,bern)
        plt.suptitle('Gradul '+str(n))
        plt.title('Timp: ' + str(round((stop-start)*1000, 2)) + "ms")
        self.canvas.draw()
    
    def next(self):
        if self.actualizare():
            self.timer.stop()
            self.update_plot()
    def play(self):
        if self.actualizare():
            self.timer.start()
    def stop(self):
        self.timer.stop()
    def reset(self):
        self.timer.stop()
        self.campN.setText("-")
        self.figure.clear()
        ax=self.figure.add_subplot()
        self.actualizare()
        ax.scatter(self.x_val,self.f(self.x_val))
        self.canvas.draw()

    def parsare_fisier(self, continut_cifre):
        ret = ""
        try:
            for curent in continut_cifre:
                if len(curent) != 0:
                    ret += str(float(curent)) + " "#convertim de la string la float si inapoi la string pentru a primi exceptie daca nr nu e convertibil la float
            self.campX.setText(ret)
        except:
            win32api.MessageBox(0, 'Fisierul contine caractere nepermise. Pot fii folosite doar numere rationale, separate de spatii, tab-uri sau enter-uri', 'Eroare', 0x00001030) 

    def liniar(self):
        self.campX.setText("liniar")
    def random(self):
        self.campX.setText("random")
    def fisier(self):
        path_fisier = filedialog.askopenfilename(filetypes=[("Toate acceptate", ".txt .tsv .csv"), ("Fisier text", ".txt"), ("Fisier excel", ".tsv .csv")])
        try:
            nume_fisier_spart = path_fisier.split(".")
            if len(nume_fisier_spart) < 2:
                raise Exception("Fisierul nu are extensie")#se va afisa mesajul din lin 285
            extensie_fisier = nume_fisier_spart[len(nume_fisier_spart) - 1]
            fisier = open(path_fisier, 'r')
            continut = fisier.read()
            fisier.close()
            if extensie_fisier == "txt" or extensie_fisier == "tsv":
                self.parsare_fisier(continut.split()) 
            elif extensie_fisier == "csv":
                self.parsare_fisier(re.split(",|\n", continut))
            else:
                win32api.MessageBox(0, 'Din pacate, acest tip de fisier nu poate fii deschis la acest moment', 'Eroare', 0x00001030) 
        except:
            win32api.MessageBox(0, 'Nu s-a putut deschide fisierul', 'Eroare', 0x00001030) 
    def click_canvas(self, event):
        if event.xdata != None:
            if self.campX.text() == "random" or self.campX.text() == "liniar":
                self.campX.setText(str(event.xdata))
            else:
                self.campX.setText(self.campX.text() + " " + str(event.xdata))

    def film(self):
        def frame_film(n):
            bern = np.zeros_like(x_val)
            for k in range(n + 1):
                bern += f(k/n * (b-a) + a)*math.comb(n,k)*t**k*(1-t)**(n-k)
            ax.plot(x_val, bern)
            plt.title('Gradul: ' + str(n))
        if self.n < 5:
            win32api.MessageBox(0, 'Nu poti salva un clip atat de scurt! Seteaza gradul polinomului la minim 5.', 'Eroare', 0x00001030) 
            return
        succes = True
        try:
            path_salvare = filedialog.asksaveasfilename(filetypes=[("Fisier video", "*.mp4")])
            metadata = dict(title = 'Polinom aproximare Bernstein')
            Writer = writers['ffmpeg']
            writer = Writer(fps = 5, metadata=metadata)
            fig = plt.figure()
            f = self.f
            a = self.a
            b = self.b
            x_val = self.x_val
            t = self.t_val
            ax = plt.axes()
            ax.scatter(x_val, f(x_val))
            nmax = self.n
            anim = FuncAnimation(fig, func = frame_film, interval = 200, frames = np.arange(1,nmax+1))
            anim.save(path_salvare, writer)
        except:
            win32api.MessageBox(0, 'Nu s-a putut salva. Extensia solcitata nu e valida.', 'Eroare', 0x00001030)
            succes = False
        finally:#daca dam sys.exit in acel try-catch, aplicatia nu se va inchide.
            if succes == True:
                win32api.MessageBox(0, 'Aplicatia acum se va inchide si vei naviga la fisier.', 'Succes', 0x00001040)
                os.startfile(path_salvare)
                sys.exit()

#Aceste 4 functii sunt responsabilitatea unui coleg in colaborare cu care am facut proiectul. Tot restul codului a fost scris de catre mine. Au fost inlocuite cu placeholdere.
    def validare_n(self):
        print("Valideaza daca campul n este un numar sau o -, coloreaza-l cu rosu daca nu. Deasemenea, n sa fie mai mic ca 1028")
        return True
    def validare_a(self):
        print("Valideaza daca campul a e nr si e mai mic ca b, coloreaza cu rosu daca daca nu")
        return True
    def validare_b(self):
        print("Valideaza daca campul b e nr si e mai mare ca a, coloreaza cu rosu daca nu")
        return True
    def validare_x(self, x):
        print("Valideaza daca ndarray-ul x dat ca parametru e ok de folosit (ex: nr sa fie intre a si b), afiseaza o eroare (win32api.MessageBox) in care explici de ce daca nu")
        return True

if __name__ == '__main__':
    app = QApplication(sys.argv)
    aproximare = Aproximare()
    aproximare.show()
    sys.exit(app.exec_())
