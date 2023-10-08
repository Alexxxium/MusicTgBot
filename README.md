# MusicTgBot

<p>
  Телеграмм бот для прослушивания музыки. Написан на языке С++ при помощи библиотеки <i><a href="https://github.com/reo7sp/tgbot-cpp">tgbot-cpp</a></i> для работы с <i><a href="https://core.telegram.org/bots/api">API Telegramm</a></i>. 
  Данный бот предназаначен для создания своего музыкального пространства, в котором вы можете создавать альбомы, загружать в них треки, давать им свои названия, а так же получать аудио по ссылке на видео с <b><i>YouTube</i></b> или на трек из <b><i>SoundCloud</i></b>. 
</p>
<i><p>ID бота: <a href="https://t.me/music_impuls_bot">@music_impuls_bot</a></p></i>

<br>
<br>

<nav>
  <h2>Навигационное меню</h2>
  <ul>
    <li><a href="https://github.com/Alexxxium/MusicTgBot#%D1%81%D0%B1%D0%BE%D1%80%D0%BA%D0%B0"><i>Собрать/установить</i></a></li>
    <li><a href="https://github.com/Alexxxium/MusicTgBot#%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F"><i>Реализация</i></a></li>
    <li><a href="https://github.com/Alexxxium/MusicTgBot#%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5"><i>Использование</i></a></li>
  </ul>
</nav>

<br>
<br>

<h2 id="1">Собрать/установить</h2>
<h3><i>Примечание:</i></h3> Бот использует <b><i>Windows API</i></b>, поэтому эта секция подойдет только для пользователей <b><i>Windows OS!</i></b>

<br>
<br>

<h3>Сборка</h3>
<p>
  <b><i>CMake!</i></b> Установите библиотеку через <b><i>vcpkg</i></b> <a href="https://github.com/reo7sp/tgbot-cpp#library-installation-on-windows"><i>tgbot-cpp</i></a>, 
  затем склонируйте репозиторий и в файле <b><i>CMakeLists.txt</i></b> в <b><i>22</i></b> строке укажите свой путь к <b><i>TgBot.lib</i></b>, а так же в файле 
  <b><i>constants/constants.cpp</i></b> в <b><i>108</i></b> строке замените мой токен на свой, его можно получить у <i><a href="https://t.me/BotFather">@BotFather</a></i>. 
  Для сборки рекомендую использовать <b><i>Microsoft Visual Studio</i></b>, так к вашим исполняемым файлам подгрузятся нужные <b><i>*.dll</i></b>, если нет, то тогда вручную скопируйте их из папки с библиотекой.
</p>
<p>
  Можно еще поиграться с кодом:<br>
  <ol>
    <li>
      <b><i>model/commands/source/AnyCommands.cpp</i></b> строка <b><i>161</i></b> - 
      передайте последним параметром в <b><i>asyncDownloader</i></b> время ожидания перед захватом файлов в <i>мс</i>. Увеличте время, если ваше соединение с интернетом не стабильно.
    </li> 
    <li>
      <b><i>server/source/ServerOperations.cpp</i></b> строка <b><i>87</i></b> - 
      передайте в <b><i>startProcess</i></b> вторым параметром таймаут (по истечении времени загрузка аудио по url завершится), третьим - паузу перед проверкой состояния процесса по загрузке, все так же в <i>мс</i>. 
      Рекомендуется увеличить время при слабом интернет соединении.
    </li>  
  </ol>
</p>
<p>
  После сборки проекта поместите в одну директорию папку <b><i>constants/messages</i></b>, скрипт <b><i>server/script.bat</i></b> и собранные исполняемые файлы вместе с необходимыми <i>dll-ками</i>. 
  Затем загрузите и распакуйте в эту же директорию <i><a href="https://github.com/yt-dlp/yt-dlp/releases/download/2023.09.24/yt-dlp.exe">yt-dlp</a></i> и 
  <i><a href="https://github.com/BtbN/FFmpeg-Builds/releases/download/latest/ffmpeg-master-latest-win64-gpl-shared.zip">ffmpeg</a></i> (все содержимое папки bin). 
  Запускайте сначала <i>Server.exe</i> а потом <i>MusicBot.exe</i>.
</p>

<br>
<br>

<h3>Установка</h3>
<p>
  Для людей: <i><a href="https://drive.google.com/drive/folders/1mJVy5q6JVyAkWtUrDoKkKKP3WvQHsss6?usp=sharing">MusicTgBot</a></i> - в папке с исполняемыми файлами создайте <b><i>token.txt</i></b> и запишите туда свой токен без пробелов.
</p>

<br>
<br>

<h2 id="2">Реализация</h2>
<p>
  Код разделен на 2 части:
  <ol>
    <li>Бот, который получает пользовательские действия и выполняет простые линейные операции</li>
    <li>Сервер, который содержит в себе многопоточную среду и выполняет ресурсозатратную логику</li>
  </ol>
Обе части писались на <b><i>MVC</i></b> архитектуре с использованием паттерна проектирования <b><i>Command</i></b>. Связь между этими двумя модулями обеспечивается за счет <b><i>клиент-серверного</i></b> кода.
</p>

<br>
<br>

<h3>Бот, который слушает...</h3>
<p>
  Вкратце, у бота есть командлет, на действия пользователя срабатывает контроллер и создает копию команды (объекта) обработки на основе нажатой кнопки, команды или отправленных данных, сохраняя контекст предыдущего сообщения. 
  Поддерживается очень легко: создаешь класс унаследованный от базового интерфейсного, определяешь метод <b><i>execute</i></b> и добавляешь его в командлет. И уже после приступаешь к линейному программированию. 
</p>
<p>
  Неплохой фишкой является захват сразу нескольких файлов/сообщений перед отправкой данных на сервер: Телеграмм поочередно доставляет нам файлы, из-за этого медиагруппу будет обрабатывать один и тот же обработчик несколько раз.
  На этот случай создается несколько <i><a href="https://github.com/Alexxxium/Algorithms/tree/master/TaskQueue">параллельных очередей</a></i> для отслеживания изменений: 
  если на протежении определенного времени не приходят аудио или url, то пользовательский ввод окончен, что так и есть! 
</p>

<br>
<br>

<h3>Сервер, который пашет...</h3>
<p>
  У сервера также есть свой командлет, который на основе полученных данных назначает обработчик и в случае успеха возвращает боту <i>HTML</i> ответ. Он предназначен для загрузки и выгрузки аудио пользователю. 
  Сервер обязуется выполнить задачу и самомтоятельно ответить пользователю. 
</p>
<p>
  Что касается загрузки треков по <i>url</i>. Я использовал <b><i>Windows API</i></b> для создания отдельных процессов в операционной системе, которые с помощью <b><i>yt-dlp</i></b> загружают аудио (для упрощения синтаксиса я вызываю <b><i>batch</i></b> скрипт). 
  За счет этого можно контролировать провалы, которые могут быть вызваны некорректными <i>url</i> адресами: иногда загрузка зацикливается или бесконечно мусорит в консоли (я тут не при чем). Так что на каждый процесс отводится время, 
  если он не успеет корректно завершиться, то его можно считать проваленным.
</p>
<p>
  Для распределения задач используется оболочка вокруг нескольких потоков (очередей) и выбирается наименее загруженная очередь.
</p>

<br>
<br>

<h2 id="3">Использование</h2>
<figure>
  <contitle><h3>Создать/переименовать</h3></contitle>
  <img src="https://raw.githubusercontent.com/Alexxxium/DocumentationSources/main/MusicTgBot/RenamePList.png?token=GHSAT0AAAAAACHC7GRPPTCPIFHZ6NLBCY2CZI64QJA", alt="Img go wor a walk">  
</figure>
<h2></h2>

<br>
<br>

<figure>
  <contitle><h3>Меню и выгрузка</h3></contitle>
  <img src="https://raw.githubusercontent.com/Alexxxium/DocumentationSources/main/MusicTgBot/PLists.png?token=GHSAT0AAAAAACHC7GROBHWP6PWIF2HKEM5CZI64SCQ", alt="Img go for a walk">
</figure>
<h2></h2>

<br>
<br>

<figure>
  <contitle><h3>Удаление и устаревшие данные</h3></contitle>
  <img src="https://raw.githubusercontent.com/Alexxxium/DocumentationSources/main/MusicTgBot/Remove.png?token=GHSAT0AAAAAACHC7GROC6HNPLPJU7QDWR72ZI64RNQ", alt="Img go for a walk">
</figure>
<h2></h2>

<br>
<br>

<figure>
  <contitle><h3>Загрузка треков</h3></contitle>
  <img src="https://raw.githubusercontent.com/Alexxxium/DocumentationSources/main/MusicTgBot/Uploading.png?token=GHSAT0AAAAAACHC7GROUKOCQVTQKV2GE57YZI64SSQ", alt="Img go for a walk">
</figure>
