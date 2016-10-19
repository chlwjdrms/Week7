#pragma once

const int width = 1500;
const int height = 480;


float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}
void Rect(const int& i4, const int& j4, const int& i5, const int& j5) {

	int k1 = i4 + (i5 - i4) / 4;
	int k2 = i5 - (i5 - i4) / 4;
	int l1 = j4 + (j5 - j4) / 4;
	int l2 = j5 - (j5 - j4) / 4;

	for (int i = k1; i <= k2; i++) {
		for (int j = l1; j <= l2; j++) {
			if (!(i > k1 + 2 && i < k2 - 2 && j > l1 + 2 && j < l2 - 2)) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
		}
	}
}