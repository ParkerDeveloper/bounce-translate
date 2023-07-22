/* Author: SR_team
 * Site: https://prime-hack.net
 * LICENSE: GPL3
 * Language: rus
 *
 * Базовый класс: QObject.
 * Класс предназначен для работы с клавишами клавиатуры и мыши.
 * Он позволяет обрабатывать следующие события:
 *										  * Зажатие клавиши
 *										  * Отпускание клавиши
 *										  * Нажатие клавиши
 *										  * Ввод кода
 *										  * Нажатие комбинации клавиш
 * Так же класс позволяет (статичные методы):
 *							  * Конвертировать код клавиши в строку и обратно
 *							  * Создавать комбинацию клавиш из строки
 *
 * От QObject классу нужны только сигналы и слоты, и если вы захотите
 * воспользоваться классом отдельно от Qt, то для реализации сигналов
 * и слотов вы можете взять мою нароботку: https://prime-hack.net/threads/2188/
 */

#ifndef SRKEYBOARD_H
#define SRKEYBOARD_H

#include <windows.h>
#include <QtCore/QObject>
#include <QList>
#include <QMap>

typedef QList<int> KeyCombo;

class SRKeys : public QObject
{
	Q_OBJECT

	friend LRESULT WINAPI WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	explicit SRKeys(QObject *parent = nullptr);
	~SRKeys();

	virtual bool isKeyDown(int key);
	virtual bool isCode(QString code);
	virtual bool isKeyComboDown(KeyCombo combo);

	virtual void addCode(QString code);
	virtual void addCombo(KeyCombo combo, QString name);

	virtual KeyCombo getCombo(QString name);

	virtual void deleteCode(QString code);
	virtual void deleteCombo(QString comboName);


	static QString getKey(int key);
	static int getKey(QString key);

	static KeyCombo createCombo(QString keys, QString sep);

protected:
	virtual void onEvent(UINT uMsg, WPARAM wParam);

signals:
	void eventKeyDown(int key);
	void eventKeyUp(int key);
	void eventKeyPressed(int key);
	void eventCode(QString code);
	void eventCombo(QString comboName);
	void eventScrollUp();
	void eventScrollDown();

private:
	QMap<int, bool>			 keyDown;
	uint8_t						code[128];
	uint						codeLen = 0;
	uint						keys;
	QMap<QString, QList<int>>   combos;
	QList<QString>			  codes;

	void processKeyDown(int key);
	void processKeyUp(int key);
	void processCodes();
	void processCombo(QString comboName);
};

#endif // SRKEYBOARD_H
