# Messenger
Это БДЗ №1.
Задача состоит в создании примитивного чата на двух пользователей с сервером на сокетах.

## server.c
Этот исходник создаёт сервер для последующего обмена сообщениями с клиентом.

### Подключаемые библиотеки и заголовочные файлы:
<stdlib.h> для подключения функции atoi, которая конвертирует строку в число.
<stdio.h> для подключения функции puts, которая выводит данные в консоль.
<string.h> для подключения функции strcmp, которая сравнивает две строки.
<sys/socket.h> - это основополагающая библиотека для данного проекта. Она используется для создания и использования сокетов на Linux.
<arpa/inet.h> для подключения функции htons, которая преобразует число с фиксированной запятой в IP адрес. Кроме того, в этой библиотеке определена INADDR_ANY, которая позволяет подключиться к любому свободному адресу связывания, а также структура sockaddr_in, которая хранит Адрес для подключения сокета.
"err_proc.h" для обработки ошибок.
"message.h" для чтения и передачи сообщений.

### Код:
```
extern const int BUFF_SIZE;
```
Дикларируем константу BUFF_SIZE, которая инициализирована в messange.c и означает размер буфера.

```
if (argc < 2) {
    puts("Not enough program arguments! Example: ./server.o <port>\n");
    return -1;
}
```
Проверяем, ввёл ли пользователь порт для подключения, если нет, завершаем программу с кодом -1 - недостаточное количество входных данных.

```
int server_socket = Socket(AF_INET, SOCK_STREAM, 0);
```
Создаём сокет, используя обёрточную функцию из файла err_proc.h, передаём на вход AF_INET - семейство протоколов, SOCK_STREAM - тип сокета (в нашем случае потоковый) и протокол (при передаче нуля, используется значение по умолчанию)

```
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(atoi(argv[1]));
addr.sin_addr.s_addr = INADDR_ANY;
```
Инициализируем структуру addr, которая хранит sin_family = AF_INET - семейство протоколов, sin_port - порт для подключения, который вводится пользователем при запуске программы и конвертируется сначала в число с помощью функции atoi, потом - в IP адрес с помощью функции htons. В addr.sin_addr.s_addr хранится адрес связывания (в нашем случае это INADDR_ANY, что означает, что нам подойдёт любой свободный адрес)

```
Bind(server_socket, (struct sockaddr*) &addr, sizeof(addr));
Listen(server_socket, 1);
```
Связываем сокет с конкретным адресом, т. е. с нашей структурой sockaddr_in addr, после чего ставим его "в режим прослушивания" в ожидании одного подключения.

```
socklen_t adrlen = sizeof addr;
int client_socket = Accept(server_socket, (struct sockaddr*) &addr, &adrlen);
```
Принимаем и инициализируем клиентский сокет.

```
char buff[BUFF_SIZE];
struct message msg;
msg.buff = buff;
msg.socket = client_socket;
```
Инициализируем структуру message msg которая хранит buff - буфер для передачи сообщений и сокет, с которым будет проводиться передача сообщений.

```
do {
    read_msg(msg);
    write_msg(msg);
} while (strcmp(msg.buff, "E\0") != 0);
```
Запускаем цикл передачи сообщений в порядки очереди, т. е. сначала сервер принимает сообщение, потом отправляет, затем снова принимает и т. д. Цикл закончится, если сервер введёт "E" или если клиент отключится (через пару проходов цикла он закончится). Функции read_msg и write_msg описаны в message.c.

```
close(client_socket);
close(server_socket);
return 0;
```
Последовательно закрываем сокет клиента и сокет сервера. Завершаем программу с кдом 0 - программа завершилась успешно.

## client.c
Этот исходник создаёт соект клиента, который подключается к серверу для последующего обмена сообщениями.

### Подключаемые библиотеки и заголовочные файлы:
<stdlib.h> для подключения функции atoi, которая конвертирует строку в число.
<stdio.h> для подключения функции puts, которая выводит данные в консоль.
<string.h> для подключения функции strcmp, которая сравнивает две строки.
<sys/socket.h> - это основополагающая библиотека для данного проекта. Она используется для создания и использования сокетов на Linux.
<arpa/inet.h> для подключения функции htons, которая преобразует число с фиксированной запятой в IP адрес. Кроме того, в этой библиотеке определена INADDR_ANY, которая позволяет подключиться к любому свободному адресу связывания, а также структура sockaddr_in, которая хранит Адрес для подключения сокета.
"err_proc.h" для обработки ошибок.
"message.h" для чтения и передачи сообщений.

### Код:
```
extern const int BUFF_SIZE;
```
Дикларируем константу BUFF_SIZE, которая инициализирована в messange.c и означает размер буфера.

```
if (argc < 2) {
    puts("Not enough program arguments! Example: ./server.o <port>\n");
    return -1;
}
```
Проверяем, ввёл ли пользователь порт для подключения, если нет, завершаем программу с кодом -1 - недостаточное количество входных данных.

```
int client_socket = Socket(AF_INET, SOCK_STREAM, 0);
```
Создаём сокет, используя обёрточную функцию из файла err_proc.h, передаём на вход AF_INET - семейство протоколов, SOCK_STREAM - тип сокета (в нашем случае потоковый) и протокол (при передаче нуля, используется значение по умолчанию)

```
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(atoi(argv[1]));
addr.sin_addr.s_addr = INADDR_ANY;
```
Инициализируем структуру addr, которая хранит sin_family = AF_INET - семейство протоколов, sin_port - порт для подключения, который вводится пользователем при запуске программы и конвертируется сначала в число с помощью функции atoi, потом - в IP адрес с помощью функции htons. В addr.sin_addr.s_addr хранится адрес связывания (в нашем случае это INADDR_ANY, что означает, что нам подойдёт любой свободный адрес)

```
Connect(client_socket, (struct sockaddr*)&addr, sizeof(addr));
```
Посылаем запрос на присоединение к серверу.

```
char buff[BUFF_SIZE];
struct message msg;
msg.buff = buff;
msg.socket = client_socket;
```
Инициализируем структуру message msg которая хранит buff - буфер для передачи сообщений и сокет, с которым будет проводиться передача сообщений.

```
do {
	write_msg(msg);
	if (strcmp(msg.buff, "E\0") == 0) { break; }
	read_msg(msg);
}
while (1);
```
Запускаем цикл передачи сообщений в порядки очереди, т. е. сначала клиент отправляет сообщение, потом принимает, затем снова отправляет и т. д. Цикл закончится, если клиент введёт "E" или если сервер отключится (через пару проходов цикла он закончится). Функции read_msg и write_msg описаны в message.c.

```
close(client_socket);
return 0;
```
Закрываем сокет клиента и завершаем программу с кодом 0 - программа завершилась успешно.

## message.h
Этот исходник содержит описание структуры message, а также декларацию функций для обмена сообщениями (чтение, отправка).

### Код
```
#pragma once
```
Нужно для того, чтобы при запуске программы заголовочный файл открывался только единожды.

```
struct message {
    int socket;
    char* buff;
};
```
Описание структуры message, которая состоит из сокета и буфера.

```
void read_msg(struct message msg);
void write_msg(struct message msg);
```
Декларация функций для считывания и записывания сообщений. Описание находится в файле message.c.

## message.c
Этот исходник содержит описание функций read_msg и write_msg.

### Подключаемые библиотеки и заголовочные файлы:
<stdio.h> для использования функций puts и fgets.
<string.h> для использования функций strlen и strcmp.
"message.h" для описания функций, расположенных в данном заголовочном файле.
"err_proc.h" для использования обёрточных функций обработки ошибок.

### Код
```
const int BUFF_SIZE = 512;
```
Инициализация константы, обозначающей размер буфера.

```
void read_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    Read(msg.socket, msg.buff, BUFF_SIZE);
    puts(msg.buff);
    if (strcmp(msg.buff, "E\0") == 0) {
        puts("Сlient has disconnected.\n");
    }
}
```
Функция read_msg читает сообщение, которое передаётся на сокет, который хранится в структуре messange msg, которая передаётся в функцию в качестве аргумента. Функция bzero отчищает первые BUFF_SIZE символов в буфере. Сохраняем полученное сообщение в буфер и выводим его на экран. Если мы получили "E", значит собеседник отключился.

```
void write_msg(struct message msg) {
    bzero(msg.buff, BUFF_SIZE);
    fgets(msg.buff, BUFF_SIZE, stdin);
    msg.buff[strlen(msg.buff) - 1] = '\0';
    write(msg.socket, msg.buff, strlen(msg.buff) * sizeof(char));
}
```
Функция write_msg передаёт по сокету, сохранённому в структуре message msg, которая передаётся в функцию в качестве аргумента, сообщение, которое пользователь вводит в консоль. Функция bzero отчищает первые BUFF_SIZE символов в буфере. Пользователь вводит в консоль сообщение, после чего мы добавляем в конец полученной строки '\0' и передаём его по сокету.

## err_proc.h
Этот исходник содержит декларацию обёрточных функций для обработки ошибок.

### Подключаемые библиотеки и заголовочные файлы:
<sys/types.h>
<sys/socket.h>
<unistd.h>

### Код
```
#pragma once
```
Нужно для того, чтобы при запуске программы заголовочный файл открывался только единожды.

```
int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr* addr, socklen_t addrlen);
ssize_t Read(int sockfd, char* buffer, int buflen)
```
Декларация функций, реализация которых прописана в err_proc.c.

## err_proc.c
Этот исходник содержит реализацию функций, продекларированных в err_proc.h.

### Подключаемые библиотеки и заголовочные файлы:
<stdlib.h>
<stdio.h>
<sys/types.h>
<sys/socket.h>
<unistd.h>
"err_proc.h"

### Код
```
int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Opening socket error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
```
Обёрточная функция для обработки ошибки при создании сокета.

```
void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Binding error!");
        exit(EXIT_FAILURE);
    }
}
```
Обёрточная функция для обработки ошибки при привязывании сокета к адресу.

```
int Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listening error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
```
Обёрточная функция для обработки ошибки при прослушивании сокетом.

```
int Accept(int sockfd, struct sockaddr* addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Accepting error!");
        exit(EXIT_FAILURE);
    }
    return res;
}
```
Обёрточная функция для обработки ошибки при принятии подключаемого сокета.

```
void Connect(int sockfd, struct sockaddr* addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connection error!");
        exit(EXIT_FAILURE);
    }
}
```
Обёрточная функция для обработки ошибки при подключении к серверу.

```
ssize_t Read(int sockfd, char* buffer, int buflen) {
    ssize_t res = read(sockfd, buffer, buflen);
    if (res == -1) {
        perror("Reading error!");
        exit(EXIT_FAILURE);
    }
    if (res == 0) { puts("Сlient has disconnected.\n"); }
    return res;
}
```
Обёрточная функция для обработки ошибки при прочтении сообщения.
