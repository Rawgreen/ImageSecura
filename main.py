# IMPORTS
import os
import sys
import subprocess


from PyQt5 import QtWidgets, uic, QtSerialPort
from PyQt5.QtWidgets import QMessageBox, QTableWidgetItem, QTreeWidgetItem
from pyqtgraph.Qt import QtGui, QtCore
from PyQt5.QtCore import QObject, QThread, pyqtSignal

import tkinter as tk
from tkinter import filedialog
from tkinter.filedialog import asksaveasfile
class Worker(QObject):
    finished = pyqtSignal()
    def newRSA(self):

        os.system('"rsa.exe"')
        self.finished.emit()
class MainWindow(QtWidgets.QMainWindow):

    def __init__(self, *args, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)

        # Load the UI Page
        uic.loadUi('Test.ui', self)
        self.encryptButton.clicked.connect(self.binaryConvert)
        self.clearButton.clicked.connect(self.clearKey)
        self.showKeyButton.clicked.connect(self.showKey)
        self.newRSAButton.clicked.connect(self.longTask)
        self.decryptButton.clicked.connect(self.decryptFunc)
    def clearKey(self):
        self.textBrowser.clear()
    def writeKey(self):
        with open("public.txt", "r") as file:
            publicKey = file.readline()
            self.textBrowser.append("Public Key:")
            self.textBrowser.append(publicKey)
        with open("private.txt","r") as file:
            privateKey=file.readline()
            self.textBrowser.append("Private Key:")
            self.textBrowser.append(privateKey)

    def binaryConvert(self):
        os.system('"img-to-binary.exe"')
        os.system('"encrypt_text.exe"')

    def showKey(self):
        self.writeKey()

    def decryptFunc(self):
        os.system('"decrypt_text.exe"')
        os.system('"binary-to-image-converter.exe"')
    def longTask(self):
        self.thread = QThread()
        self.worker = Worker()
        self.worker.moveToThread(self.thread)
        self.thread.started.connect(self.worker.newRSA)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        self.textBrowser.append("Thread Started:")
        self.thread.start()
        self.newRSAButton.setEnabled(False)
        self.thread.finished.connect(lambda: self.textBrowser.append("Thread Finished:"))
        self.thread.finished.connect(lambda: self.newRSAButton.setEnabled(True))

def main():
    app = QtWidgets.QApplication(sys.argv)
    main = MainWindow()
    main.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()