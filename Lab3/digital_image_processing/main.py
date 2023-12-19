import sys
import cv2
import numpy as np
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QPushButton, QHBoxLayout, QVBoxLayout, QFileDialog
from PyQt5.QtGui import QImage, QPixmap, QPainter
from PyQt5.QtCore import QRectF, QSize, Qt


class ImageProcessingApp(QWidget):
    def __init__(self):
        super().__init__()

        self.image_path = None

        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Основы обработки цифровых изображений")

        self.image_label = QLabel(self)
        self.image_label.setFixedSize(900, 600)

        self.button_select = QPushButton('Выбрать изображение', self)
        self.button_select.clicked.connect(self.select_image)

        self.button_sharpen = QPushButton('Увеличение резкости', self)
        self.button_sharpen.clicked.connect(self.apply_sharpen_filter)
        self.button_sharpen.setEnabled(False)

        self.button_contrast = QPushButton('Линейное контрастирование', self)
        self.button_contrast.clicked.connect(self.apply_linear_contrast)
        self.button_contrast.setEnabled(False)

        self.button_equalize_rgb = QPushButton('Выравнивание гистограммы (RGB)', self)
        self.button_equalize_rgb.clicked.connect(self.equalize_histogram_rgb)
        self.button_equalize_rgb.setEnabled(False)

        self.button_equalize_hsv = QPushButton('Выравнивание гистограммы (HSV)', self)
        self.button_equalize_hsv.clicked.connect(self.equalize_histogram_hsv)
        self.button_equalize_hsv.setEnabled(False)

        button_layout = QHBoxLayout()
        button_layout.addWidget(self.button_select)
        button_layout.addWidget(self.button_sharpen)
        button_layout.addWidget(self.button_contrast)
        button_layout.addWidget(self.button_equalize_rgb)
        button_layout.addWidget(self.button_equalize_hsv)

        main_layout = QVBoxLayout()
        main_layout.addWidget(self.image_label)
        main_layout.addLayout(button_layout)

        self.setLayout(main_layout)

    def select_image(self):
        file_dialog = QFileDialog()
        file_path, _ = file_dialog.getOpenFileName(self, 'Выберите изображение', '', 'Изображения (*.png *.jpg *.jpeg)')
        if file_path:
            self.image_path = file_path
            self.show_image()

    def enable_buttons(self):
        self.button_sharpen.setEnabled(True)
        self.button_contrast.setEnabled(True)
        self.button_equalize_rgb.setEnabled(True)
        self.button_equalize_hsv.setEnabled(True)

    def apply_sharpen_filter(self):
        if self.image_path:
            image = cv2.imread(self.image_path)

            if image is not None:
                sharpened_image = cv2.filter2D(image, -1, np.array([[-1, -1, -1], [-1, 9, -1], [-1, -1, -1]]))
                self.show_image(sharpened_image)

    def apply_linear_contrast(self):
        if self.image_path:
            image = cv2.imread(self.image_path)

            if image is not None:
                contrasted_image = cv2.convertScaleAbs(image, alpha=1.6, beta=5)
                self.show_image(contrasted_image)

    def equalize_histogram_rgb(self):
        if self.image_path:
            image = cv2.imread(self.image_path)

            if image is not None:
                equalized_image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
                equalized_image[:, :, 0] = cv2.equalizeHist(equalized_image[:, :, 0])
                equalized_image[:, :, 1] = cv2.equalizeHist(equalized_image[:, :, 1])
                equalized_image[:, :, 2] = cv2.equalizeHist(equalized_image[:, :, 2])
                equalized_image = cv2.cvtColor(equalized_image, cv2.COLOR_RGB2BGR)
                self.show_image(equalized_image)

    def equalize_histogram_hsv(self):
        if self.image_path:
            image = cv2.imread(self.image_path)

            if image is not None:
                hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
                hsv_image[:, :, 2] = cv2.equalizeHist(hsv_image[:, :, 2])
                equalized_image = cv2.cvtColor(hsv_image, cv2.COLOR_HSV2BGR)
                self.show_image(equalized_image)

    def show_image(self, image=None):
        if image is None and self.image_path:
            image = cv2.imread(self.image_path)

        if image is not None:
            height, width, channel = image.shape
            bytes_per_line = channel * width
            q_image = QImage(image.data, width, height, bytes_per_line, QImage.Format_BGR888)
            pixmap = QPixmap.fromImage(q_image)

            if pixmap.width() > pixmap.height():
                target_width = self.image_label.width()
                target_height = int(pixmap.height() * target_width / pixmap.width())
            else:
                target_height = self.image_label.height()
                target_width = int(pixmap.width() * target_height / pixmap.height())

            pic_size = QSize(target_width, target_height)
            pixmap = pixmap.scaled(pic_size, Qt.AspectRatioMode.KeepAspectRatio)

            self.image_label.setPixmap(pixmap)
            self.enable_buttons()

    def resizeEvent(self, event):
        if self.image_label.pixmap() is not None:
            pixmap = self.image_label.pixmap()
            self.image_label.setFixedSize(pixmap.width(), pixmap.height())
        event.accept()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = ImageProcessingApp()
    widget.show()
    sys.exit(app.exec())
