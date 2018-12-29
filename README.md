# Robocup2019 Графы

### Работаем с Git:
Что бы код не превратился в недоразумение, следует придерживаться нескольким правлилам:

1) Комитим только в __свою__ ветку

2) Кидаем пул реквест в __develop__

3) Ждём пока пул реквест __одобрят__

### Работаем с make

Что бы установить утилиту make, следует выполнить

--> sudo apt-get install make

#### параметры __Makefile__ :

1) __CONFI_NAME__ - имя конфигурации в qibuild. По умолчанию linux-sdk

2) __GEN_NAME__ - имя скрипта python, генерирующего граф. По умолчанию generator.py

3) __IP__ - IP адрес робота. По умолчанию 192.168.1.2

4) __VERTEXSET__ - путь до хранилища вершин

5) __EDGESET__ - путь до хранилища рёбер

6) __OUTPUT__ - код графа на С++

#### Цели __Makefile__ :

1) __all__ - цель по умолчанию. Генерирует, компилирует и запускает код.

2) __gen__ - генерирует граф по файлам ./test/vertex.txt ./test/edge.txt с помощью GEN_NAME

3) __compil__ - компилирует код с помощью qibuild и конфигурации CONFIG_NAME

4) __run__ - запускает скомпилированный модуль.

5) __clear__ - удаляет всё ненужное.

#### Пример использования:

--> make

--> make CONFIG_NAME=LinuxSDK IP=192.168.1.8

--> make clear

make clear CONFIG_NAME=LinuxSDK






## Погружаемся в идею:

### Идея, первое погружение:
Построим граф, где точкой будет локальное положение робота. Локальным положением я называю совокупность положений суставов и значений датчиков (x, y координату относительно поля мы не рассматриваем).

Свяжем две точки A, B ориентированным ребром, если из положения A мы можем перейти в положение B некоторым лёгким алгоритмом.

Таким образом мы получили граф, передвигаясь по рёбрам которого мы будем менять локальное положение робота нужным нам образом.

## Мотивация первого погружения:
Зачем это надо? Дело в том, что в процессе игры в футбол у робота будет много локальных положений, и зачастую нам потребуется переходить из одного локального положение в другое (примеры локальных положений: упал (лежит), сидит, перенёс вес на левую\правую ногу, стоит на двух ногах, делает шаг (одна нога впереди), ...). Если всё "хардкодить" - записывать все передвижения в отдельную функцию, то функций получится O(n 2) (каждый с каждым), но если делать согласно методу первого погружения, нам будет достаточно захардкодить O(n) рёбер, а дальше просто искать путь в графе.

## Вопрос к первому погружению:
Хорошо, а что делать если мы сбоем пришли в позицию, которая не была ранееcd . захардкодина?

## Идея, второе погружение:
По сути, у нас есть ~22 мерное пространство локальных положений (по количеству датчиков и моторчиков) и мы хардкодим какие-то точки из этого пространства. Будем считать точки близкими, если мы можем перевести одну в другую просто независимо изменив значения каждого моторчика. Например, лежать с вытянутыми ногами и лежать с чуть подобранными - близкие точки.

Назовём захардкоденые точки опорными. Множество близких точек к захардкоденым - окрестность опорной точки.

Наша задача - покрыть всё пространство объеденением окрестностей опорных точек, и как-нибудь связать полученный граф.

По сути, если отбросить скептический настрой, у нас получится бесконечный связный граф, по которому мы можем перемещаться и решать более сложные задачи. Просто хранить мы будим только опорные точки и рёбра между ними. Рёбра между опорными и точкой локального положения мы будем хранить неявно - это, по сути, одно и то же ребро с функцией последовательного (в любом порядке) перевода моторчиков из положения A в положение B.

## Вопрос ко второму погружению:
Что за дичь? Никакой алгоритм нахождения минимального пути не будет работать быстро на бесконечном графе!

## Ответ скептикам (хейтерам):
Зачем нам переходить в точку локального положения, если опорные точки "хорошо" покрывают всё пространство?

Из предположения, что конечной точкой может быть только опорная и из знания того, что всякая точка локального положения соединена ребром с опорной, следует что обычная ширина будет работать за O(N + E).

## Вопрос ко второму погружению:
Хорошо, но перемещаясь по рёбрам мы можем перемещаться в глобальном пространстве (относительно поля), про которое мы забыли. Как то не очень приятно.

## Идея, третье погружение:
Справедливо, давайте запишем на каждом ребре вектор перемещение робота относительно поля. Таким образом, мы сможем не просто искать путь в графе опорных точек, но искать путь перемещающий робота в нужную точку относительно поля. Это же конечный автомат? Отдельно стоит сказать про рёбра между локальным положением робота и опорной точкой - оно не изменяет глобального положения.

## Мотивация третьего погружения:
Таким образом, у нас получится реализовать такое поведение:
--> Робот идёт к мячу
--> Его толкнули, он упал
--> Робот сам поднялся
--> Робот продолжил идти к мячу

Как это сделать? Следует в вершине проверять, что наше предполагаемое локальное положение совпадает с реальным (проверять данные с датчиков и моторчиков). Если это не выполнено найдём ближайшую опорную точку и пересчитаем путь до цели.

## Задачи:
Предполагаю что нужно реализовывать этот алгоритм по погружениям.
Задачи на первое погружение:

1) Придумать удобную архитектуру графа, вершин, рёбер, и главного модуля move

2) Написать хороший алгоритм поиска пути в графе

3) Захордкодить точки и рёбра

4) Протестировать всё это.

### Цель первого погружения:
Научить робота ходить