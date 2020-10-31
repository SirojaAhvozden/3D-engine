#include "Texture.h"

bool getTexture(GLuint* texture, std::string name, ILenum tip) {

	glGenTextures(1, texture);

	GLubyte* imageData;
	ilLoad(tip, name.c_str());
	// Проверяем, нет ли ошибок при открытии файла
	int err = ilGetError();
	if (err != IL_NO_ERROR)
	{
		const char* strError = iluErrorString(err);
		std::cout << strError << "\n";
		return -1;
	}
	// Получаем данные текстуры
	int width = ilGetInteger(IL_IMAGE_WIDTH);          // Ширина
	int height = ilGetInteger(IL_IMAGE_HEIGHT);        // Высота
	int size = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);      // Байт на пиксел
	// Загружаем данные в нашу текстуру
	imageData = ilGetData();
	ilEnable(IL_CONV_PAL);
	// Тип данных изображения
	unsigned int type = ilGetInteger(IL_IMAGE_FORMAT);

	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	return 0;
}