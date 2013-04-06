%module(directors="1") jddesvr
%include "std_string.i"

%{
#include "aquila/jddesvr/Cell.h"
#include "aquila/jddesvr/Table.h"
#include "aquila/jddesvr/ServiceHandler.h"
#include "aquila/jddesvr/Server.h"
%}

%typemap(out) std::string
%{  // BEG typemap(out) std::string marker
  size_t $1_len = $1.length();
  wchar_t *$1_dst = new wchar_t[$1_len];
  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, $1.c_str(), $1_len, $1_dst, $1_len);
  $result = jenv->NewString((jchar*)$1_dst, $1_len);
  delete [] $1_dst;
  // END typemap(out) std::string marker %}
  
%typemap(directorin,descriptor="Ljava/lang/String;") std::string 
%{  // BEG typemap(directorin,descriptor="Ljava/lang/String;") std::string
  size_t $1_len = $1.length();
  wchar_t *$1_dst = new wchar_t[$1_len];
  MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, $1.c_str(), $1_len, $1_dst, $1_len);
  $input = jenv->NewString((jchar*)$1_dst, $1_len);
  delete [] $1_dst;
  // END typemap(directorin,descriptor="Ljava/lang/String;") std::string %}

%javamethodmodifiers aquila::jddesvr::ServiceHandler::ServiceHandler(string serviceName) "
  /**
   * Создать объект
   * <p>
   * @param serviceName идентификатор сервиса
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::getName() "
  /**
   * Получить наименование сервиса DDE
   * <p>
   * @return строковый идентификатор сервиса
   */
  public final";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::onConnect(string topic) "
  /**
   * Обработчик события XTYP_CONNECT
   * <p>
   * @param topic строка темы
   * @return true - разрешить подключение, false - отклонить
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::onConnectConfirm(string topic) "
  /**
   * Обработчик события XTYP_CONNECT_CONFIRM
   * <p>
   * @param topic строка темы
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::onRawData(string topic, string item,
		char* dataBuffer, int size) "
  /**
   * Обработчик события XTYP_POKE
   * <p>
   * @param topic строка темы
   * @param item строка субъекта
   * @param dataBuffer массив данных (возможность сохранения ссылки не проверена)
   * @return true - данные обработаны и вызывать {@link #onData} не нужно,
   * false - необходим разбор данных как XLT-таблицы и вызов метода {@link #onData}.
   */
  public";

%javamethodmodifiers aquila::jddesvr::ServiceHandler::onData(Table table) "
  /**
   * Обработчик входящей XLT-таблицы
   * <p>
   * Данный метод должен реализовывать вызывается в случае, если метод
   * {@link #onRawData} вернул false. В этом случае входной массив байт
   * разбирается как XLT-таблица и передается в данный обработчик.
   * <p>
   * @param table таблица
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::onDisconnect(string topic) "
  /**
   * Обработчик события XTYP_DISCONNECT
   * <p>
   * @param topic строка темы
   */
  public";

%javamethodmodifiers aquila::jddesvr::ServiceHandler::onRegister() "
  /**
   * Обработчик события XTYP_REGISTER
   * <p>
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::ServiceHandler::onUnregister() "
  /**
   * Обработчик события XTYP_UNREGISTER
   * <p>
   */
  public";

%typemap(javaimports) aquila::jddesvr::ServiceHandler "
/**
 * Обработчик событий DDE-сервера.
 * <p>
 * 2011-01-01<br>
 * $Id: jddesvr.i 543 2013-02-25 06:35:27Z whirlwind $
 */"

%javamethodmodifiers aquila::jddesvr::Cell::isFloat() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - ячейка вещественного типа, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isBoolean() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - ячейка булева типа, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isString() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - ячейка строкового типа, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isInteger() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - ячейка целого типа, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isError() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - ячейка типа ошибка, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isBlank() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - пустая ячейка, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::isSkip() "
  /**
   * Проверить тип ячейки
   * <p>
   * @return true - пропуск ячейки, false - иначе
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::asFloat() "
  /**
   * Получить значение ячейки
   * <p>
   * @return значение ячейки
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::asBoolean() "
  /**
   * Получить значение ячейки
   * <p>
   * @return значение ячейки
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::asString() "
  /**
   * Получить значение ячейки
   * <p>
   * @return значение ячейки
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Cell::asInteger() "
  /**
   * Получить значение ячейки
   * <p>
   * @return значение ячейки
   */
  public";

%typemap(javaimports) aquila::jddesvr::Cell "
/**
 * Прокси-класс к C++ реализации ячейки таблицы.
 * Данный класс не следует инстанцировать из java кода.
 * <p>
 * 2011-01-01<br>
 * $Id: jddesvr.i 543 2013-02-25 06:35:27Z whirlwind $
 */";
%typemap(javaclassmodifiers) aquila::jddesvr::Cell "public final class";

%javamethodmodifiers aquila::jddesvr::Table::getTopic() "
  /**
   * Получить тему
   * <p>
   * @return тема таблицы
   */
  public final";

%javamethodmodifiers aquila::jddesvr::Table::getItem() "
  /**
   * Получить субъект
   * <p>
   * @return субъект таблицы
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Table::getRows() "
  /**
   * Получить количество строк
   * <p>
   * @return количество строк
   */
  public";
 
%javamethodmodifiers aquila::jddesvr::Table::getCols() "
  /**
   * Получить количество колонок
   * <p>
   * @return количество колонок
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Table::getCell(int row, int col) "
  /**
   * Получить ячейку
   * <p>
   * @param row индекс строки
   * @param col индекс колонки
   * @return количество строк
   */
  public";

%typemap(javaimports) aquila::jddesvr::Table "
/**
 * Прокси-класс к C++ реализации таблицы.
 * Данный класс не следует инстанцировать из java кода.
 * <p>
 * 2011-01-01<br>
 * $Id: jddesvr.i 543 2013-02-25 06:35:27Z whirlwind $
 */";
%typemap(javaclassmodifiers) aquila::jddesvr::Table "public final class";

%javamethodmodifiers aquila::jddesvr::Server::Server() "
  /**
   * Создать объект
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Server::start() "
  /**
   * Запустить DDE-сервер
   */
  public";

%javamethodmodifiers aquila::jddesvr::Server::stop() "
  /**
   * Остановить DDE-сервер
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Server::join() "
  /**
   * Ожидать завершения DDE-сервера
   */
  public";

%javamethodmodifiers aquila::jddesvr::Server::registerService(ServiceHandler service) "
  /**
   * Зарегистрировать обработчик DDE-транзакций
   */
  public";
  
%javamethodmodifiers aquila::jddesvr::Server::unregisterService(ServiceHandler service) "
  /**
   * Удалить обработчик DDE-транзакций
   */
  public";

%typemap(javaimports) aquila::jddesvr::Server "
/**
 * Прокси-класс к C++ реализации DDE-сервера.
 * <p>
 * 2011-01-01<br>
 * $Id: jddesvr.i 543 2013-02-25 06:35:27Z whirlwind $
 */";
%typemap(javaclassmodifiers) aquila::jddesvr::Server "public final class";

%pragma(java) jniclasscode=%{
  static {
	String arch = System.getProperty("os.arch");
	if ( ! "x86".equals(arch) ) {
		System.err.println("jddesvr supports only x86 architecture because no 64-bit version of TRANS2QUIK.dll.");
		System.exit(1);
	}
    try {
        System.loadLibrary("jddesvr");
    } catch ( UnsatisfiedLinkError e ) {
      System.err.println("Native code library failed to load. \n" + e);
      System.exit(1);
    }
  }
%}

%typemap(directorin, descriptor="[B") (char *STRING, size_t LENGTH) { 
	$input = (jenv)->NewByteArray(size); 
    (jenv)->SetByteArrayRegion($input, 0, size, (jbyte*)dataBuffer); 
}

%feature("director") ServiceHandler; 
%typemap(throws, throws="Exception") std::exception, exception {
    jclass exClass = jenv->FindClass("java/lang/Exception");
    if (exClass)
        jenv->ThrowNew(exClass, $1.what());
    return $null;
}

%apply (char *STRING, size_t LENGTH) { (char* dataBuffer, int size) };
%newobject aquila::jddesvr::Table::makeCopy();

%include "aquila/jddesvr/Cell.h"
%include "aquila/jddesvr/Table.h"
%include "aquila/jddesvr/ServiceHandler.h"
%include "aquila/jddesvr/Server.h"
