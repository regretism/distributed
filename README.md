В данной работе продемонстрирован пример работы простейшего распределенного приложения. Приложение написано на C.

Приложение содержит два файла: client.c и server.c, они реализуют работу приложения со стороны клиента и сервера соответственно.

Алгоритм работы:

server.c:
1.Инициализация библиотеки Winsock.
2.Создание сокета для сервера.
3.Настройка параметров сервера, таких как семейство протоколов, IP-адрес и порт.
4.Привязка сокета к указанному адресу.
5.Ожидание подключения клиента с использованием функции listen.
6.Принятие подключения с использованием функции accept.
7.Обмен данными с клиентом в цикле, используя функции recv и send.
8.Закрытие сокетов и очистка ресурсов при завершении работы сервера.

client.c

1.Инициализация библиотеки Winsock и WS2tcpip.
2.Создание сокета для клиента.
3.Настройка параметров сервера, таких как семейство протоколов, IP-адрес и порт.
4.Подключение к серверу с использованием функции connect.
5.Отправка данных на сервер с использованием функции send.
6.Получение ответа от сервера с использованием функции recv.
7.Закрытие сокета и очистка ресурсов при завершении работы клиента.


Пример работы приложения:

![image](https://github.com/regretism/distributed/assets/85019980/7443c86f-d329-4b35-8034-217ed2ac9c55)


Запуск:

Для запуска приложения необходимо открыть distributedserver.exe в терминале, затем открыть distributed.exe в терминале.

Убедитесь, что вы открыли два разных терминала.

Результат должен выглядеть следующим образом: 

![image](https://github.com/regretism/distributed/assets/85019980/531a78b4-3a15-44fa-85e1-8bf3b54ac386)