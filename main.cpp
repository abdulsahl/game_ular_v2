/*
List Kelompok:
Kelas B
1. 230411100003, Harits Putra Junaidi
2. 230411100086, Danendra Mahardhika
3. 230411100059, Achmad Lutfi Madhani
4. 230411100104 Moch Sigit Aringga
5. 230411100090, Abdullah Sahl
6. 230411100166, Dicky Prasetyo
*/

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <iostream>

// Ukuran papan
#define COLS 7
#define ROWS 12


bool is3D = false;

float rotateX = -10.0f;
float rotateY = 0.0f;


float observerX = -0.97f;
float observerY = -0.95f;
float observerSize = 0.03f;

// Asumsi batas papan di koordinat OpenGL:
const float batasKiri = -1.0f + 0.05f;
const float batasKanan = 1.0f - 0.05f;
const float batasBawah = -1.0f + 0.05f;
const float batasAtas = 1.0f - 0.05f;


void drawGreenLine(float x1, float y1, float x2, float y2, float width, float zOffset) {
    if (is3D) {
        glColor3f(0.49f, 0.69f, 0.01f);

        float depth = 0.03f;
        float halfWidth = width / 2.0f;

        // Titik-titik dasar dari balok (8 titik)
        float x1a = x1, x2a = x2;
        float y1u = y1 + halfWidth, y1b = y1 - halfWidth;
        float y2u = y2 + halfWidth, y2b = y2 - halfWidth;
        float z1 = zOffset;
        float z2 = zOffset - depth;

        glBegin(GL_POLYGON);
        // Atas
        glVertex3f(x1a, y1u, z1);
        glVertex3f(x2a, y2u, z1);
        glVertex3f(x2a, y2u, z2);
        glVertex3f(x1a, y1u, z2);

        // Bawah
        glVertex3f(x1a, y1b, z1);
        glVertex3f(x2a, y2b, z1);
        glVertex3f(x2a, y2b, z2);
        glVertex3f(x1a, y1b, z2);

        // Kiri
        glVertex3f(x1a, y1u, z1);
        glVertex3f(x1a, y1b, z1);
        glVertex3f(x1a, y1b, z2);
        glVertex3f(x1a, y1u, z2);

        // Kanan
        glVertex3f(x2a, y2u, z1);
        glVertex3f(x2a, y2b, z1);
        glVertex3f(x2a, y2b, z2);
        glVertex3f(x2a, y2u, z2);

        // Depan
        glVertex3f(x1a, y1u, z1);
        glVertex3f(x2a, y2u, z1);
        glVertex3f(x2a, y2b, z1);
        glVertex3f(x1a, y1b, z1);

        // Belakang
        glVertex3f(x1a, y1u, z2);
        glVertex3f(x2a, y2u, z2);
        glVertex3f(x2a, y2b, z2);
        glVertex3f(x1a, y1b, z2);
        glEnd();
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
        glVertex2f(x1, y1 + width / 2);
        glVertex2f(x2, y2 + width / 2);
        glVertex2f(x2, y2 - width / 2);
        glVertex2f(x1, y1 - width / 2);
        glEnd();
    }
}


void drawSegment3D(float x1, float y1, float x2, float y2, float z1, float z2) {
    glBegin(GL_POLYGON);
    // Depan
    glVertex3f(x1, y1, z1); glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1); glVertex3f(x1, y2, z1);

    // Belakang
    glVertex3f(x1, y1, z2); glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2); glVertex3f(x1, y2, z2);

    // Kanan
    glVertex3f(x2, y1, z1); glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2); glVertex3f(x2, y1, z2);

    // Kiri
    glVertex3f(x1, y1, z1); glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2); glVertex3f(x1, y1, z2);

    // Atas
    glVertex3f(x1, y2, z1); glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2); glVertex3f(x1, y2, z2);

    // Bawah
    glVertex3f(x1, y1, z1); glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2); glVertex3f(x1, y1, z2);
    glEnd();
}

//Fungsi untuk menggambar digit angka
void drawDigit(int digit, float x, float y, float size, float zOffset) {
    float seg = size / 5.0f;
    float z1 = zOffset;
    float z2 = zOffset - 0.02f;

    switch (digit) {
        case 0:
            if (is3D) {
                drawSegment3D(x, y, x + seg, y + size, z1, z2);
                drawSegment3D(x + size - seg, y, x + size, y + size, z1, z2);
                drawSegment3D(x, y + size - seg, x + size, y + size, z1, z2);
                drawSegment3D(x, y, x + size, y + seg, z1, z2);
            } else {
                // Kiri
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + seg, y);
                glVertex2f(x + seg, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Kanan
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + size);
                glVertex2f(x + size - seg, y + size);
                glEnd();

                // Atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size - seg);
                glVertex2f(x + size, y + size - seg);
                glVertex2f(x + size, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Bawah
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + seg);
                glVertex2f(x, y + seg);
                glEnd();
            }
            break;

        case 3:
            if (is3D) {
                drawSegment3D(x, y + size - seg, x + size, y + size, z1, z2);
                drawSegment3D(x, y + size / 2 - seg / 2, x + size, y + size / 2 + seg / 2, z1, z2);
                drawSegment3D(x, y, x + size, y + seg, z1, z2);
                drawSegment3D(x + size - seg, y, x + size, y + size, z1, z2);
            } else {
                // Atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size - seg);
                glVertex2f(x + size, y + size - seg);
                glVertex2f(x + size, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Tengah
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 + seg / 2);
                glVertex2f(x, y + size / 2 + seg / 2);
                glEnd();

                // Bawah
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + seg);
                glVertex2f(x, y + seg);
                glEnd();

                // Kanan penuh
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + size);
                glVertex2f(x + size - seg, y + size);
                glEnd();
            }
            break;

        case 5:
            if (is3D) {
                drawSegment3D(x, y + size - seg, x + size, y + size, z1, z2);
                drawSegment3D(x, y + size / 2 - seg / 2, x + size, y + size / 2 + seg / 2, z1, z2);
                drawSegment3D(x, y, x + size, y + seg, z1, z2);
                drawSegment3D(x, y + size / 2, x + seg, y + size, z1, z2);
                drawSegment3D(x + size - seg, y, x + size, y + size / 2, z1, z2);
            } else {
                // Atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size - seg);
                glVertex2f(x + size, y + size - seg);
                glVertex2f(x + size, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Tengah
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 + seg / 2);
                glVertex2f(x, y + size / 2 + seg / 2);
                glEnd();

                // Bawah
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + seg);
                glVertex2f(x, y + seg);
                glEnd();

                // Kiri atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2);
                glVertex2f(x + seg, y + size / 2);
                glVertex2f(x + seg, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Kanan bawah
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + size / 2);
                glVertex2f(x + size - seg, y + size / 2);
                glEnd();
            }
            break;

        case 6:
            if (is3D) {
                drawSegment3D(x, y + size - seg, x + size, y + size, z1, z2);
                drawSegment3D(x, y + size / 2 - seg / 2, x + size, y + size / 2 + seg / 2, z1, z2);
                drawSegment3D(x, y, x + size, y + seg, z1, z2);
                drawSegment3D(x, y + size / 2, x + seg, y + size, z1, z2);
                drawSegment3D(x, y, x + seg, y + size / 2, z1, z2);
                drawSegment3D(x + size - seg, y, x + size, y + size / 2, z1, z2);
            } else {
                // Atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size - seg);
                glVertex2f(x + size, y + size - seg);
                glVertex2f(x + size, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Tengah
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 + seg / 2);
                glVertex2f(x, y + size / 2 + seg / 2);
                glEnd();

                // Bawah
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + seg);
                glVertex2f(x, y + seg);
                glEnd();

                // Kiri atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2);
                glVertex2f(x + seg, y + size / 2);
                glVertex2f(x + seg, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Kiri bawah
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + seg, y);
                glVertex2f(x + seg, y + size / 2);
                glVertex2f(x, y + size / 2);
                glEnd();

                // Kanan tengah
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + size / 2);
                glVertex2f(x + size - seg, y + size / 2);
                glEnd();
            }
            break;

        case 9:
            if (is3D) {
                drawSegment3D(x, y + size - seg, x + size, y + size, z1, z2);
                drawSegment3D(x, y + size / 2 - seg / 2, x + size, y + size / 2 + seg / 2, z1, z2);
                drawSegment3D(x + size - seg, y + size / 2, x + size, y + size, z1, z2);
                drawSegment3D(x + size - seg, y, x + size, y + size / 2, z1, z2);
                drawSegment3D(x, y + size / 2, x + seg, y + size, z1, z2);
                drawSegment3D(x, y, x + size, y + seg, z1, z2);
            } else {
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size - seg);
                glVertex2f(x + size, y + size - seg);
                glVertex2f(x + size, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Tengah
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 - seg / 2);
                glVertex2f(x + size, y + size / 2 + seg / 2);
                glVertex2f(x, y + size / 2 + seg / 2);
                glEnd();

                // Kanan atas
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y + size / 2);
                glVertex2f(x + size, y + size / 2);
                glVertex2f(x + size, y + size);
                glVertex2f(x + size - seg, y + size);
                glEnd();

                // Kanan bawah
                glBegin(GL_POLYGON);
                glVertex2f(x + size - seg, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size, y + size / 2);
                glVertex2f(x + size - seg, y + size / 2);
                glEnd();

                // Kiri atas
                glBegin(GL_POLYGON);
                glVertex2f(x, y + size / 2);
                glVertex2f(x + seg, y + size / 2);
                glVertex2f(x + seg, y + size);
                glVertex2f(x, y + size);
                glEnd();

                // Kiri bawah pendek
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + size, y);
                glVertex2f(x + size / 2, y + seg);
                glVertex2f(x, y + seg);
                glEnd();
            }
            break;

        default:
            break;
    }
}

void drawNumber(const char* str, float x, float y, float size, float spacing) {
    for (int i = 0; str[i] != '\0'; i++) {
        int digit = str[i] - '0';
        drawDigit(digit, x, y, 0.04f, is3D ? 0.05f : 0.0f);
        x += size + spacing;
    }
}

// Fungsi untuk menggambar objek observer
void observer(float x, float y, float radius) {
    glPushMatrix();
    glTranslatef(x, y, is3D ? 0.02f : 0.0f);

    glColor3f(0.5925f, 0.5925f, 0.5925f);

    GLdouble height = is3D ? radius * 2 : 0.001;
    glutSolidCone(radius, height, 20, 20);

    glPopMatrix();
}



// Fungsi untuk memeriksa apakah nomor sel mengandung digit NRP
int containsNRPDigit(int cellNum) {
    // Digit terakhir NRP: 0, 3, 4, 6, 9

    int temp = cellNum;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0 || digit == 3 || digit == 4 || digit == 6 || digit == 9) {
            return 1;
        }
        temp /= 10;
    }

    if (cellNum == 0) {
        return 1;
    }

    return 0;
}

int isPartOfSpecialPair(int cellNum) {
    int specialPairs[] = {7, 8, 14, 15, 21, 22, 28, 29, 35, 36, 42, 43, 49, 50, 56, 57, 63, 64, 70, 71, 77, 78};
    int numSpecialPairs = sizeof(specialPairs) / sizeof(specialPairs[0]);

    for (int i = 0; i < numSpecialPairs; i++) {
        if (cellNum == specialPairs[i]) {
            return 1;
        }
    }
    return 0;
}

int checkIsUpOrDown(int num) {
    int special_num[] = {1, 2, 3, 4, 5, 6, 7, 78, 79, 80, 81, 82, 83, 84};

    for (int i = 0; i < sizeof(special_num) / sizeof(special_num[0]); ++i) {
        if (special_num[i] == num) {
            return 1;
        }
    }

    return 0;
}

int formSpecialPair(int cell1, int cell2) {
    int specialPairs[][2] = {
        {7, 8}, {14, 15}, {21, 22}, {28, 29}, {35, 36},
        {42, 43}, {49, 50}, {56, 57}, {63, 64}, {70, 71}, {77, 78}
    };
    int numPairs = sizeof(specialPairs) / sizeof(specialPairs[0]);

    for (int i = 0; i < numPairs; i++) {
        if ((cell1 == specialPairs[i][0] && cell2 == specialPairs[i][1]) ||
            (cell1 == specialPairs[i][1] && cell2 == specialPairs[i][0])) {
            return 1;
        }
    }
    return 0;
}

// Fungsi untuk menggambar papan
void drawBoard() {
    float cellWidth = 2.0f / COLS;
    float cellHeight = 2.0f / ROWS;
    float horizontalGapSize = 0.01f;
    int cellNumbers[ROWS][COLS];

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (row % 2 == 0) {
                // Baris genap (0, 2, 4, ...) - dari kiri ke kanan
                cellNumbers[row][col] = row * COLS + col + 1;
            } else {
                // Baris ganjil (1, 3, 5, ...) - dari kanan ke kiri
                cellNumbers[row][col] = row * COLS + (COLS - col);
            }
        }
    }

    // Gambar petak-petak
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            int cellNum = cellNumbers[row][col];

            float x = -1.0f + col * cellWidth;
            float y = -1.0f + row * cellHeight;
            float topGap = horizontalGapSize;
            float bottomGap = horizontalGapSize;

            if (row > 0) {
                int cellAbove;
                if ((row-1) % 2 == 0) {
                    cellAbove = cellNumbers[row-1][col];
                } else {
                    cellAbove = cellNumbers[row-1][col];
                }

                if (formSpecialPair(cellNum, cellAbove)) {
                    topGap = 0.0f;
                }
            }

            if (row < ROWS - 1) {
                int cellBelow;
                if ((row+1) % 2 == 0) {
                    cellBelow = cellNumbers[row+1][col];
                } else {
                    cellBelow = cellNumbers[row+1][col];
                }

                if (formSpecialPair(cellNum, cellBelow)) {
                    bottomGap = 0.0f;
                }
            }

            // Hilangkan gap bawah untuk cell 1 sampai 7
            if (cellNum >= 1 && cellNum <= 7) {
                topGap = 0.0f;
            }

            // Hilangkan gap atas untuk cell 78 sampai 84
            if (cellNum >= 78 && cellNum <= 84) {
                bottomGap = 0.0f;
            }


            y += topGap;
            float actualCellHeight = cellHeight - topGap - bottomGap;

            if ((row + col) % 2 == 0) {
                if (is3D) {

                    glColor4f(0.0f, 0.0f, 0.5f, 0.9f);

                } else {
                    glColor3f(0.0f, 0.0f, 1.0f);
                }
            } else {
                if (is3D) {
                    glColor4f(0.2f, 0.2f, 0.2f, 0.7f);
                } else {
                    glColor3f(1.0f, 1.0f, 0.9f);
                }
            }

            if (is3D) {

                float z0 = -0.04f;
                float zBack = -0.01f;

                // Atas (permukaan petak)
                glBegin(GL_POLYGON);
                glVertex3f(x, y, z0);
                glVertex3f(x + cellWidth, y, z0);
                glVertex3f(x + cellWidth, y + actualCellHeight, z0);
                glVertex3f(x, y + actualCellHeight, z0);
                glEnd();

                // Depan
                glBegin(GL_POLYGON);
                glVertex3f(x, y, zBack);
                glVertex3f(x + cellWidth, y, zBack);
                glVertex3f(x + cellWidth, y, z0);
                glVertex3f(x, y, z0);
                glEnd();

                // Kanan
                glBegin(GL_POLYGON);
                glVertex3f(x + cellWidth, y, zBack);
                glVertex3f(x + cellWidth, y + actualCellHeight, zBack);
                glVertex3f(x + cellWidth, y + actualCellHeight, z0);
                glVertex3f(x + cellWidth, y, z0);
                glEnd();

                // Belakang
                glBegin(GL_POLYGON);
                glVertex3f(x, y + actualCellHeight, zBack);
                glVertex3f(x + cellWidth, y + actualCellHeight, zBack);
                glVertex3f(x + cellWidth, y + actualCellHeight, z0);
                glVertex3f(x, y + actualCellHeight, z0);
                glEnd();

                // Kiri
                glBegin(GL_POLYGON);
                glVertex3f(x, y, zBack);
                glVertex3f(x, y + actualCellHeight, zBack);
                glVertex3f(x, y + actualCellHeight, z0);
                glVertex3f(x, y, z0);
                glEnd();

                // Bawah (opsional - biasanya tak terlihat)
                glBegin(GL_POLYGON);
                glVertex3f(x, y, zBack);
                glVertex3f(x + cellWidth, y, zBack);
                glVertex3f(x + cellWidth, y + actualCellHeight, zBack);
                glVertex3f(x, y + actualCellHeight, zBack);
                glEnd();

            } else {
                // Mode 2D tetap pakai glVertex2f
                glBegin(GL_POLYGON);
                glVertex2f(x, y);
                glVertex2f(x + cellWidth, y);
                glVertex2f(x + cellWidth, y + actualCellHeight);
                glVertex2f(x, y + actualCellHeight);
                glEnd();
            }

            char numStr[4];
            sprintf(numStr, "%d", cellNum);
            char filteredStr[4] = "";
            int filteredIndex = 0;

            for (int i = 0; numStr[i] != '\0'; i++) {
                char digit = numStr[i];
                if (digit == '0' || digit == '3' || digit == '4' || digit == '6' || digit == '9') {
                    filteredStr[filteredIndex++] = digit;
                }
            }
            filteredStr[filteredIndex] = '\0';

            // Tampilkan teks jika ada digit yang tersisa
            if (filteredIndex > 0) {
                // Warna nomor
                glColor3f(0.75f, 0.6f, 0.22f);
                glLineWidth(2.0f);
                drawNumber(filteredStr, x + cellWidth * 0.6f, y + actualCellHeight * 0.6f, 0.03f, 0.020f);
            }
        }
    }
}

// fungsi untuk menggambar pagar tepi
void pagar(float xMin, float xMax, float yMin, float yMax, float borderWidth, bool is3D) {
    if (is3D) {
        glColor3f(0.49f, 0.69f, 0.01f);
        float z1 = 0.02f;
        float z2 = -0.04f;

        // Pagar atas (z1 dan z2 = kedalaman)
        glBegin(GL_QUADS);
        glVertex3f(xMin - borderWidth, yMax, z1);
        glVertex3f(xMax + borderWidth, yMax, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z1);

        glVertex3f(xMin - borderWidth, yMax, z2);
        glVertex3f(xMax + borderWidth, yMax, z2);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z2);
        glEnd();

        // Sisi pagar atas
        glBegin(GL_QUADS);
        glVertex3f(xMin - borderWidth, yMax, z1);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMax, z2);

        glVertex3f(xMax + borderWidth, yMax, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMax + borderWidth, yMax, z2);

        glVertex3f(xMin - borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z2);

        glVertex3f(xMin - borderWidth, yMax, z1);
        glVertex3f(xMax + borderWidth, yMax, z1);
        glVertex3f(xMax + borderWidth, yMax, z2);
        glVertex3f(xMin - borderWidth, yMax, z2);
        glEnd();

        // Pagar bawah dan sisi-sisinya
        glBegin(GL_QUADS);
        glVertex3f(xMin - borderWidth, yMin, z1);
        glVertex3f(xMax + borderWidth, yMin, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z1);

        glVertex3f(xMin - borderWidth, yMin, z2);
        glVertex3f(xMax + borderWidth, yMin, z2);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z2);

        glVertex3f(xMin - borderWidth, yMin, z1);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMin, z2);

        glVertex3f(xMax + borderWidth, yMin, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z2);
        glVertex3f(xMax + borderWidth, yMin, z2);

        glVertex3f(xMin - borderWidth, yMin - borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z2);

        glVertex3f(xMin - borderWidth, yMin, z1);
        glVertex3f(xMax + borderWidth, yMin, z1);
        glVertex3f(xMax + borderWidth, yMin, z2);
        glVertex3f(xMin - borderWidth, yMin, z2);
        glEnd();

        // Pagar kiri dan kanan
        glBegin(GL_QUADS);
        // kiri
        glVertex3f(xMin, yMin - borderWidth, z1);
        glVertex3f(xMin, yMax + borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z1);

        glVertex3f(xMin, yMin - borderWidth, z2);
        glVertex3f(xMin, yMax + borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMin - borderWidth, yMin - borderWidth, z2);

        // kanan
        glVertex3f(xMax, yMin - borderWidth, z1);
        glVertex3f(xMax, yMax + borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z1);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z1);

        glVertex3f(xMax, yMin - borderWidth, z2);
        glVertex3f(xMax, yMax + borderWidth, z2);
        glVertex3f(xMax + borderWidth, yMax + borderWidth, z2);
        glVertex3f(xMax + borderWidth, yMin - borderWidth, z2);

        // Tambahan sisi dalam pagar kiri (dalam arah Z)
        glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f - borderWidth, z1);
        glVertex3f(-1.0f, 1.0f + borderWidth, z1);
        glVertex3f(-1.0f, 1.0f + borderWidth, z2);
        glVertex3f(-1.0f, -1.0f - borderWidth, z2);
        glEnd();

        // Tambahan sisi dalam pagar kanan (dalam arah Z)
        glBegin(GL_QUADS);
        glVertex3f(1.0f, -1.0f - borderWidth, z1);
        glVertex3f(1.0f, 1.0f + borderWidth, z1);
        glVertex3f(1.0f, 1.0f + borderWidth, z2);
        glVertex3f(1.0f, -1.0f - borderWidth, z2);
        glEnd();

        glEnd();
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
        glVertex2f(xMin - borderWidth, yMax);
        glVertex2f(xMax + borderWidth, yMax);
        glVertex2f(xMax + borderWidth, yMax + borderWidth);
        glVertex2f(xMin - borderWidth, yMax + borderWidth);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(xMin - borderWidth, yMin);
        glVertex2f(xMax + borderWidth, yMin);
        glVertex2f(xMax + borderWidth, yMin - borderWidth);
        glVertex2f(xMin - borderWidth, yMin - borderWidth);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(xMin, yMin - borderWidth);
        glVertex2f(xMin, yMax + borderWidth);
        glVertex2f(xMin - borderWidth, yMax + borderWidth);
        glVertex2f(xMin - borderWidth, yMin - borderWidth);
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(xMax, yMin - borderWidth);
        glVertex2f(xMax, yMax + borderWidth);
        glVertex2f(xMax + borderWidth, yMax + borderWidth);
        glVertex2f(xMax + borderWidth, yMin - borderWidth);
        glEnd();
    }
}

// Fungsi untuk membuat tangga
void tangga(float startX, float startY, float width, float height, int numRungs, float angle, float thickness, float zOffset) {
    float rungSpacing = height / (numRungs + 1);
    float depth = 0.05f;

    glPushMatrix();
    glTranslatef(startX + width / 2, startY, zOffset);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-startX - width / 2, -startY, -zOffset);

    if (is3D) {
        glColor3f(0.6f, 0.3f, 0.0f);

        // Tiang kiri 3D
        glBegin(GL_POLYGON);
        // Depan
        glVertex3f(startX, startY, zOffset);
        glVertex3f(startX + thickness, startY, zOffset);
        glVertex3f(startX + thickness, startY + height, zOffset);
        glVertex3f(startX, startY + height, zOffset);

        // Belakang
        glVertex3f(startX, startY, zOffset - depth);
        glVertex3f(startX + thickness, startY, zOffset - depth);
        glVertex3f(startX + thickness, startY + height, zOffset - depth);
        glVertex3f(startX, startY + height, zOffset - depth);

        // Sisi samping kiri
        glVertex3f(startX, startY, zOffset);
        glVertex3f(startX, startY, zOffset - depth);
        glVertex3f(startX, startY + height, zOffset - depth);
        glVertex3f(startX, startY + height, zOffset);

        // Sisi samping kanan tiang kiri
        glVertex3f(startX + thickness, startY, zOffset);
        glVertex3f(startX + thickness, startY, zOffset - depth);
        glVertex3f(startX + thickness, startY + height, zOffset - depth);
        glVertex3f(startX + thickness, startY + height, zOffset);
        glEnd();

        // Tiang kanan 3D
        float xRight = startX + width - thickness;
        glBegin(GL_POLYGON);
        // Depan
        glVertex3f(xRight, startY, zOffset);
        glVertex3f(xRight + thickness, startY, zOffset);
        glVertex3f(xRight + thickness, startY + height, zOffset);
        glVertex3f(xRight, startY + height, zOffset);

        // Belakang
        glVertex3f(xRight, startY, zOffset - depth);
        glVertex3f(xRight + thickness, startY, zOffset - depth);
        glVertex3f(xRight + thickness, startY + height, zOffset - depth);
        glVertex3f(xRight, startY + height, zOffset - depth);

        // Sisi samping kiri tiang kanan
        glVertex3f(xRight, startY, zOffset);
        glVertex3f(xRight, startY, zOffset - depth);
        glVertex3f(xRight, startY + height, zOffset - depth);
        glVertex3f(xRight, startY + height, zOffset);

        // Sisi samping kanan
        glVertex3f(xRight + thickness, startY, zOffset);
        glVertex3f(xRight + thickness, startY, zOffset - depth);
        glVertex3f(xRight + thickness, startY + height, zOffset - depth);
        glVertex3f(xRight + thickness, startY + height, zOffset);
        glEnd();

        for (int i = 1; i <= numRungs; i++) {
            float rungY = startY + i * rungSpacing;
            float x1 = startX + thickness;
            float x2 = startX + width - thickness;
            float y1 = rungY - thickness / 2;
            float y2 = rungY + thickness / 2;

            glBegin(GL_POLYGON);
            // Depan
            glVertex3f(x1, y1, zOffset);
            glVertex3f(x2, y1, zOffset);
            glVertex3f(x2, y2, zOffset);
            glVertex3f(x1, y2, zOffset);

            // Belakang
            glVertex3f(x1, y1, zOffset - depth);
            glVertex3f(x2, y1, zOffset - depth);
            glVertex3f(x2, y2, zOffset - depth);
            glVertex3f(x1, y2, zOffset - depth);

            // Atas
            glVertex3f(x1, y2, zOffset);
            glVertex3f(x2, y2, zOffset);
            glVertex3f(x2, y2, zOffset - depth);
            glVertex3f(x1, y2, zOffset - depth);

            // Bawah
            glVertex3f(x1, y1, zOffset);
            glVertex3f(x2, y1, zOffset);
            glVertex3f(x2, y1, zOffset - depth);
            glVertex3f(x1, y1, zOffset - depth);
            glEnd();
        }
    } else {
        glColor3f(0.6f, 0.3f, 0.0f);
        // Tiang kiri
        glBegin(GL_POLYGON);
        glVertex2f(startX, startY);
        glVertex2f(startX + thickness, startY);
        glVertex2f(startX + thickness, startY + height);
        glVertex2f(startX, startY + height);
        glEnd();

        // Tiang kanan
        glBegin(GL_POLYGON);
        glVertex2f(startX + width - thickness, startY);
        glVertex2f(startX + width, startY);
        glVertex2f(startX + width, startY + height);
        glVertex2f(startX + width - thickness, startY + height);
        glEnd();

        // Anak tangga
        for (int i = 1; i <= numRungs; i++) {
            float rungY = startY + i * rungSpacing;
            glBegin(GL_POLYGON);
            glVertex2f(startX + thickness, rungY - thickness / 2);
            glVertex2f(startX + width - thickness, rungY - thickness / 2);
            glVertex2f(startX + width - thickness, rungY + thickness / 2);
            glVertex2f(startX + thickness, rungY + thickness / 2);
            glEnd();
        }
    }

    glPopMatrix();
}

void ular(float startX, float startY, float endX, float endY, float thickness, int numSegments, float zOffset) {
    glColor3f(1.0f, 0.0f, 0.0f);


    float dx = endX - startX;
    float dy = endY - startY;
    float length = sqrt(dx * dx + dy * dy);

    float nx = dx / length;
    float ny = dy / length;

    float perpX = -ny;
    float perpY = nx;

    float controlPoints[20][2];
    int numControls = numSegments + 1;

    for (int i = 0; i < numControls; i++) {
        float t = (float)i / (numControls - 1);
        controlPoints[i][0] = startX + t * dx;
        controlPoints[i][1] = startY + t * dy;
        if (i > 0 && i < numControls - 1) {
            float offset = (i % 2 == 0) ? 0.15f : -0.15f;
            controlPoints[i][0] += perpX * length * offset;
            controlPoints[i][1] += perpY * length * offset;
        }
    }

    float depth = 0.05f;

    for (int i = 0; i < numControls - 1; i++) {
        float segDx = controlPoints[i+1][0] - controlPoints[i][0];
        float segDy = controlPoints[i+1][1] - controlPoints[i][1];
        float segLen = sqrt(segDx * segDx + segDy * segDy);

        float segNx = segDx / segLen;
        float segNy = segDy / segLen;

        float segPerpX = -segNy;
        float segPerpY = segNx;

        float x1a = controlPoints[i][0] + segPerpX * thickness / 2;
        float y1a = controlPoints[i][1] + segPerpY * thickness / 2;
        float x2a = controlPoints[i+1][0] + segPerpX * thickness / 2;
        float y2a = controlPoints[i+1][1] + segPerpY * thickness / 2;

        float x2b = controlPoints[i+1][0] - segPerpX * thickness / 2;
        float y2b = controlPoints[i+1][1] - segPerpY * thickness / 2;
        float x1b = controlPoints[i][0] - segPerpX * thickness / 2;
        float y1b = controlPoints[i][1] - segPerpY * thickness / 2;

        if (is3D) {
            glBegin(GL_POLYGON);
            // Atas (depan)
            glVertex3f(x1a, y1a, zOffset);
            glVertex3f(x2a, y2a, zOffset);
            glVertex3f(x2b, y2b, zOffset);
            glVertex3f(x1b, y1b, zOffset);

            // Bawah (belakang)
            glVertex3f(x1a, y1a, zOffset - depth);
            glVertex3f(x2a, y2a, zOffset - depth);
            glVertex3f(x2b, y2b, zOffset - depth);
            glVertex3f(x1b, y1b, zOffset - depth);

            // Sisi kanan
            glBegin(GL_POLYGON);
            glVertex3f(x2a, y2a, zOffset);
            glVertex3f(x2a, y2a, zOffset - depth);
            glVertex3f(x1a, y1a, zOffset - depth);
            glVertex3f(x1a, y1a, zOffset);
            glEnd();

            // Sisi kiri
            glBegin(GL_POLYGON);
            glVertex3f(x1b, y1b, zOffset);
            glVertex3f(x1b, y1b, zOffset - depth);
            glVertex3f(x2b, y2b, zOffset - depth);
            glVertex3f(x2b, y2b, zOffset);
            glEnd();

        } else {
            glBegin(GL_POLYGON);
            glVertex2f(x1a, y1a);
            glVertex2f(x2a, y2a);
            glVertex2f(x2b, y2b);
            glVertex2f(x1b, y1b);
            glEnd();
        }
    }
}


void persegi(float x, float y, float size, float red, float green, float blue, float zOffset) {
    glColor3f(red, green, blue);

    if (is3D) {
        float depth = 0.05f;
        float x1 = x;
        float x2 = x + (size + 0.01f);
        float y1 = y + 0.01f;
        float y2 = y + size;
        float z1 = zOffset;
        float z2 = zOffset - depth;

        glBegin(GL_POLYGON);
        // DEPAN
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x1, y2, z1);

        // BELAKANG
        glVertex3f(x1, y1, z2);
        glVertex3f(x2, y1, z2);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        // ATAS
        glVertex3f(x1, y2, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y2, z2);

        // BAWAH
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y1, z2);
        glVertex3f(x1, y1, z2);

        // KANAN
        glVertex3f(x2, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x2, y1, z2);

        // KIRI
        glVertex3f(x1, y1, z1);
        glVertex3f(x1, y2, z1);
        glVertex3f(x1, y2, z2);
        glVertex3f(x1, y1, z2);
        glEnd();
    } else {
        glBegin(GL_POLYGON);
        glVertex2f(x, y + 0.01f);
        glVertex2f(x + (size + 0.01f), y + 0.01f);
        glVertex2f(x + (size + 0.01f), y + size);
        glVertex2f(x, y + size);
        glEnd();
    }
}


void segitiga(float x, float y, float size, float red, float green, float blue, float zOffset) {
    glColor3f(red, green, blue);

    float height = size * sqrt(3.0f) / 2.0f;

    if (is3D) {
        float depth = 0.05f;

        // Titik-titik
        float x1 = x;
        float y1 = y;
        float x2 = x + size;
        float y2 = y;
        float x3 = x + size / 2.0f;
        float y3 = y + height;

        float z1 = zOffset;
        float z2 = zOffset - depth;

        // SISI DEPAN
        glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x3, y3, z1);
        glEnd();

        // SISI BELAKANG
        glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, z2);
        glVertex3f(x3, y3, z2);
        glVertex3f(x2, y2, z2);
        glEnd();

        // SISI KIRI
        glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x3, y3, z1);
        glVertex3f(x3, y3, z2);
        glVertex3f(x1, y1, z2);
        glEnd();

        // SISI KANAN
        glBegin(GL_POLYGON);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x3, y3, z2);
        glVertex3f(x3, y3, z1);
        glEnd();

        // SISI BAWAH
        glBegin(GL_POLYGON);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x1, y1, z2);
        glEnd();

    } else {
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + size, y);
        glVertex2f(x + size / 2, y + height);
        glEnd();
    }
}

int currentPlayer = 0;
int playerPositions[2] = {1, 1};
int diceResult = 0;
int gameOver = 0;

// Koordinat pemain
float triangleX = -0.93f;
float triangleY = -0.93f;
float squareX = -0.85f;
float squareY = -0.95f;


float playerCoordinates[ROWS][COLS][2];
int tanggaMulai[] = {13, 36, 71};
int tanggaAkhir[] = {44, 62, 75};
int ularMulai[] = {35, 69, 76};
int ularAkhir[] = {9, 31, 12};


//lempar dadu
int rollDice() {
    return (rand() % 6) + 1; // Angka 1-6
}

// Fungsi untuk mengkonversi nomor sel ke koordinat baris dan kolom
void getCellPosition(int cellNum, int* row, int* col) {
    cellNum = cellNum - 1;
    *row = cellNum / COLS;

    if (*row % 2 == 0) {
        *col = cellNum % COLS;
    } else {
        *col = COLS - 1 - (cellNum % COLS);
    }
}

// Fungsi untuk mendapatkan koordinat gambar di sel tertentu
void getDrawCoordinatesForCell(int cellNum, float* x, float* y, int playerId) {
    if (cellNum < 1 || cellNum > ROWS * COLS) {
        *x = -0.9f;
        *y = -0.9f;
        return;
    }

    int row, col;
    getCellPosition(cellNum, &row, &col);

    float cellWidth = 2.0f / COLS;
    float cellHeight = 2.0f / ROWS;

    float baseX = -1.0f + col * cellWidth + cellWidth * 0.25f;
    float baseY = -1.0f + row * cellHeight + cellHeight * 0.25f;

    if (playerId == 0) {
        *x = baseX;
        *y = baseY + cellHeight * 0.15f;
    } else {
        *x = baseX + cellWidth * 0.30f;
        *y = baseY;
    }
}

// Fungsi untuk memeriksa apakah pemain berada di awal tangga atau ular
void checkLaddersAndSnakes(int playerIndex) {
    int position = playerPositions[playerIndex];

    for (int i = 0; i < 3; i++) {
        if (position == tanggaMulai[i]) {
            playerPositions[playerIndex] = tanggaAkhir[i];
            printf("Player %d naik tangga dari %d ke %d\n", playerIndex + 1, position, tanggaAkhir[i]);
            return;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (position == ularMulai[i]) {
            playerPositions[playerIndex] = ularAkhir[i];
            printf("Player %d turun ular dari %d ke %d\n", playerIndex + 1, position, ularAkhir[i]);
            return;
        }
    }
}

float step = 0.02f;
float rotStep = 1.0f;

// Fungsi input
void input(unsigned char key, int x, int y) {
    if (key == ' ' && !gameOver) {
        diceResult = rollDice();
        printf("Player %d melempar dadu: %d\n", currentPlayer + 1, diceResult);
        playerPositions[currentPlayer] += diceResult;

        if (playerPositions[currentPlayer] >= ROWS * COLS) {
            playerPositions[currentPlayer] = ROWS * COLS;
            printf("Player %d menang!\n", currentPlayer + 1);
            gameOver = 1;
        } else {
            checkLaddersAndSnakes(currentPlayer);
        }

        if (currentPlayer == 0) {
            getDrawCoordinatesForCell(playerPositions[0], &triangleX, &triangleY, 0);

        } else {
            getDrawCoordinatesForCell(playerPositions[1], &squareX, &squareY, 1);
        }
        currentPlayer = 1 - currentPlayer;
        glutPostRedisplay();

    } else if (key == 'r' || key == 'R') {

        playerPositions[0] = 1;
        playerPositions[1] = 1;
        currentPlayer = 0;
        gameOver = 0;

        triangleX = -0.93f;
        triangleY = -0.93f;
        squareX = -0.85f;
        squareY = -0.95f;

        printf("Game direset\n");
        glutPostRedisplay();
    } else if (key == 'v' || key == 'V'){
        is3D = !is3D;
        glutPostRedisplay();
    } else if (key == 'w' || key == 'W') {
        if (observerY <= 0.95f) {
            observerY += step;
            glutPostRedisplay();
        }
    } else if (key == 's' || key == 'S') {

        if (observerY >= -0.95f) {
            observerY -= step;
            glutPostRedisplay();
        }
    } else if (key == 'a' || key == 'A') {
        if (observerX > -0.97f) {
            observerX -= step;
            glutPostRedisplay();
        }
    } else if (key == 'd' || key == 'D') {
        if (observerX <= 0.95f) {
            observerX += step;
            glutPostRedisplay();
        }
    } else if (key == 'i' || key == 'I') {
        rotateX -= rotStep;
        glutPostRedisplay();
    } else if (key == 'k' || key == 'K') {
        rotateX += rotStep;
        glutPostRedisplay();
    } else if (key == 'j' || key == 'J') {
        rotateY -= rotStep;
        glutPostRedisplay();
    } else if (key == 'l' || key == 'L') {
        rotateY += rotStep;
        glutPostRedisplay();
    }
}

void display() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!is3D) {
        glDisable(GL_DEPTH_TEST);
    } else {
        glEnable(GL_DEPTH_TEST);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (is3D) {
        gluPerspective(40.0, 1.0, 1.0, 10.0);
    } else {
        glOrtho(-1.1f, 1.1f, -1.1f, 1.1f, -1.0f, 1.0f);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (is3D) {
        glTranslatef(0.0f, 0.0f, -3.0f);
        glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    drawBoard();

    glDepthMask(GL_TRUE);

    //pagar gap hijau
    drawGreenLine(-1.0f, -0.83f, -1.0f + (2.0f / COLS * 6), -0.83f, 0.025f, 0.0f);
    drawGreenLine(1.0f, -0.67f, -0.712f, -0.67f, 0.025f, 0.0f);
    drawGreenLine(-1.0f, -0.50f, -1.0f + (2.0f / COLS * 6), -0.50f, 0.025f, 0.0f);
    drawGreenLine(1.0f, -0.33f, -0.712f, -0.33f, 0.025f, 0.0f);
    drawGreenLine(-1.0f, -0.17f, -1.0f + (2.0f / COLS * 6), -0.17f, 0.025f, 0.0f);
    drawGreenLine(1.0f, -0.00f, -0.712f, -0.00f, 0.025f, 0.0f);
    drawGreenLine(-1.0f, 0.17f, -1.0f + (2.0f / COLS * 6), 0.17f, 0.025f, 0.0f);
    drawGreenLine(1.0f, 0.33f, -0.712f, 0.33f, 0.025f, 0.0f);
    drawGreenLine(-1.0f, 0.50f, -1.0f + (2.0f / COLS * 6), 0.50f, 0.025f, 0.0f);
    drawGreenLine(1.0f, 0.67f, -0.712f, 0.67f, 0.025f, 0.0f);
    drawGreenLine(-1.0f, 0.83f, -1.0f + (2.0f / COLS * 6), 0.83f, 0.025f, 0.0f);

     // Tangga
    tangga(-0.68f, -0.78f, 0.22f, 0.85f, 4, 0, 0.018f, 0.05f);
    tangga(0.2f, 0.75f, 0.13f, 1.1f, 4, 90, 0.018f, 0.05f);
    tangga(0.77f, -0.1f, 0.22f, 0.6f, 4, 30, 0.018f, 0.05f);

    //ular
    ular(0.5f, 0.72f, -0.2f, -0.75f, 0.025f, 3, 0.05f);  // tengah
    ular(-0.6f, 0.55f, -0.3f, -0.2f, 0.025f, 3, 0.05f);  // kiri
    ular(0.8f, -0.3f, 0.6f, -0.75f, 0.025f, 3, 0.05f);   // kanan

    // Player 1
    segitiga(triangleX, triangleY, 0.05f, 0.0f, 1.0f, 0.0f, is3D ? 0.05f : 0.0f);

    // Player 2
    persegi(squareX, squareY, 0.05f, 1.0f, 0.0f, 0.0f, is3D ? 0.015f : 0.0f);

    //observer
    observer(observerX, observerY, observerSize);
    //pagar
    pagar(-1.0f, 1.0f, -1.0f, 1.0f, 0.02f, is3D);

    glutSwapBuffers();
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glutKeyboardFunc(input);
    srand(time(NULL));
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glDisable(GL_CULL_FACE);

    glutInitWindowSize(500, 700);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Ular Tangga");

    printf("===== PERMAINAN TANGGA & ULAR =====\n");
    printf("Petunjuk:\n");
    printf("- Tekan SPASI untuk melempar dadu dan bermain\n");
    printf("- Pemain 1: Segitiga (Hijau)\n");
    printf("- Pemain 2: Persegi (Kuning)\n");
    printf("Selamat bermain!\n\n");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
