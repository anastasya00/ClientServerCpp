# ClientServerCpp

## Описание

Проект состоит из двух программ, взаимодействие между которыми осуществляется через сокеты:

1. **Программа №1 (Клиент)**:
   - Состоит из двух потоков и общего буфера.
   - Поток 1 обрабатывает ввод пользователя: проверяет строку, сортирует, заменяет чётные элементы и помещает результат в буфер.
   - Поток 2 обрабатывает данные из буфера, вычисляет сумму численных значений и отправляет её во вторую программу.

2. **Программа №2 (Сервер)**:
   - Принимает данные от клиента, анализирует их длину и кратность 32, затем выводит результат.

## Требования

Для сборки и запуска проекта необходимы:

- CMake версии 3.22 или выше
- Компилятор C++ с поддержкой стандарта C++17 или выше (например, g++, clang++)
- Linux или другая совместимая Unix-система

---

## Установка и сборка

1. В корневой директории выполните команду создания директории build и сборки проекта:

   ```bash
   mkdir build && cd build && cmake -S .. -B . && cmake --build .
   ```

3. После успешной сборки в директории `build/src` появятся исполняемые файлы клиента и сервера, соответственно `mainClient`, `mainServer`.

---

### Запуск клиента

1. 
   ```bash
   ./src/mainClient
   ```

2. Введите строку (только цифры, не более 64 символов).

---

### Запуск сервера

1.
   ```bash
   ./src/mainServer
   ```

---

## Использование

1. Соберите проект.
2. Запустите клиент (Программа №1).
3. Запустите сервер (Программа №2).
4. Взаимодействуйте с программами:
   - Вводите данные в клиенте.
   - Наблюдайте результаты анализа данных на сервере.
