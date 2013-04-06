/**
 * ============================================================================
 * 2011/08/11
 * $Id: SleshLibrary.cpp 465 2013-01-31 12:43:14Z whirlwind $
 * ============================================================================
 */
#include "aquila/core/SleshLibrary.h"
#include <vector>

namespace aquila {
	namespace core {

#define MAX_SECTIONS 10  // максимальное кол-во секций в файле

typedef unsigned long ULONG, *PULONG;
typedef unsigned short USHORT, *PUSHORT;

#pragma warning(disable: 4200)
// структура для релоков
typedef struct _FIXREC {
	ULONG	PageRVA;
	ULONG	BlockSize;
	USHORT	TOR[];
} TFIXREC,*PFIXREC;

// структура таблицы импорта
typedef struct _IMPORT_TABLE
{
	ULONG LookUp;
	ULONG TimeStamp;
	ULONG ForwardChain;
	ULONG NameRVA;
	ULONG AddresTableRVA;
} IMPORT_TABLE, *PIMPORT_TABLE;

#pragma pack(1) // отключаем выравнение
// структура таблица адресов
typedef struct _ADDRESS_TABLE {
	USHORT Hint;
	char Name[];
} ADDRESS_TABLE, *PADDRESS_TABLE;
#pragma pack() // выключаем выравнение
#pragma warning(default: 4200)

void tokenize(const string& str,
			  vector<string>& tokens,
			  const string& delimiters)
{
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while ( string::npos != pos || string::npos != lastPos ) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

bool is_file_exists(const char* filename) {
	HANDLE hFile = ::CreateFile(filename,
		0,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN,
		NULL);
	if ( INVALID_HANDLE_VALUE != hFile ) {
		::CloseHandle(hFile);
		return true;
	}
	return false;
}

string find_module_path(const char* moduleName) {
	if ( is_file_exists(moduleName) ) {
		return moduleName;
	}
	char buffer[32767];
	::GetEnvironmentVariable("PATH", buffer, sizeof(buffer));
	string path(buffer);
	vector<string> tokens;
	tokenize(path, tokens, ";");
	::GetCurrentDirectory(sizeof(buffer), buffer);
	tokens.push_back(buffer);
	for ( int i = 0; i < tokens.size(); i ++ ) {
		path = tokens[i];
		path += "\\";
		path += moduleName;
		if ( is_file_exists(path.c_str()) ) {
			return path;
		}
	}
	path = "Module not found: ";
	path += moduleName;
	throw DllException(path.c_str());
}

SleshLibrary::SleshLibrary(const char* moduleName) {
	find_module_path(moduleName);
	hmod = NULL;
	string error;
	ULONG retadr = 0;
	DWORD rb;
	HANDLE hFile;
	IMAGE_DOS_HEADER DosHeader;
	IMAGE_NT_HEADERS PeHeader;
	IMAGE_SECTION_HEADER Section[MAX_SECTIONS];
	char tmp[1024];

	// откроем файл на чтение
	string path = find_module_path(moduleName);
	hFile = CreateFileA(path.c_str(),
		GENERIC_READ, FILE_SHARE_READ,
		0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if ( hFile == INVALID_HANDLE_VALUE ) {
		getLastError(error, "CreateFile");
		error += ": ";
		error += moduleName;
		throw DllException(error.c_str());
	}

	// считаем DOS заголовок
	if ( ReadFile(hFile, &DosHeader, sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 ) {
		getLastError(error, "ReadFile");
		CloseHandle(hFile);
		throw DllException(error.c_str());
	}

	if (DosHeader.e_magic == IMAGE_DOS_SIGNATURE) { // проверим сигнатуру
		// если есть какимето данные между DOS заголовком и PE 
		// то считаем их. В MS компиляторах это часто Rich данные
		if (sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew) {
			if ( ReadFile(hFile, &tmp[0], DosHeader.e_lfanew -
				sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 )
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
		}
		// установим указатель в файле на PE заголовок
		if ( SetFilePointer(hFile, DosHeader.e_lfanew, 0, FILE_BEGIN) ==
			INVALID_SET_FILE_POINTER )
		{
			getLastError(error, "SetFilePointer");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}
		// считаем заголовок
		if ( ReadFile(hFile, &PeHeader, sizeof(IMAGE_NT_HEADERS), &rb, 0) == 0 ) {
			getLastError(error, "ReadFile");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}

		if ( PeHeader.Signature == IMAGE_NT_SIGNATURE ) { // проверим сигнатуру
			// считаем 10 секций
			if ( ReadFile(hFile, &Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections, &rb, 0) == 0 ) 
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			// выделим память столько, сколько указано в SIZE OF BASE
			retadr = (ULONG)VirtualAlloc(0, PeHeader.OptionalHeader.SizeOfImage,
				MEM_COMMIT | MEM_RESERVE | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
			if ( retadr == NULL ) {
				getLastError(error, "VirtualAlloc");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			
			// скопируем туда DOS заголовок
			memcpy((void*) retadr, &DosHeader, sizeof(IMAGE_DOS_HEADER));
			// скопируем туда PE заголовок
			memcpy((void*)(retadr + DosHeader.e_lfanew), &PeHeader,
				sizeof(IMAGE_NT_HEADERS));
			// скопируем туда таблицу секций
			memcpy((void*)(retadr + DosHeader.e_lfanew + sizeof(IMAGE_NT_HEADERS)),
				&Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections);
			// если есть Rich данные то и их тоже скопируем
			if ( sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew )  {
				memcpy((void*)(retadr + sizeof(IMAGE_DOS_HEADER)), &tmp[0],
					DosHeader.e_lfanew - sizeof(IMAGE_DOS_HEADER));
			}
			// обработаем каждую секцию
			for ( int i = 0; i < PeHeader.FileHeader.NumberOfSections; i++ ){
				// установим указатель в файле не начало секции в файле
				if ( SetFilePointer(hFile, Section[i].PointerToRawData, 0, FILE_BEGIN) ==
					INVALID_SET_FILE_POINTER )
				{
					getLastError(error, "SetFilePointer");
					CloseHandle(hFile);
					VirtualFree((LPVOID)retadr, 0, MEM_RELEASE); // очищаем память
					throw DllException(error.c_str());
				}
				// считаем всё секцию
				if ( ReadFile(hFile, (void*)(retadr + Section[i].VirtualAddress),
					Section[i].SizeOfRawData, &rb,0) == 0 )
				{
					getLastError(error, "ReadFile");
					CloseHandle(hFile);
					VirtualFree((LPVOID)retadr, 0, MEM_RELEASE);
					throw DllException(error.c_str());
				}
			}

			CloseHandle(hFile);

			// Обработаем релоки
			try {
				progressReloc(retadr);
				progressImport(retadr);
			} catch ( DllException e ) {
				VirtualFree((LPVOID)retadr, 0, MEM_RELEASE);
				throw DllException(e.what());
			}

			__asm {
				mov eax, PeHeader.OptionalHeader.AddressOfEntryPoint
				add eax, retadr // EAX = ENTRY POINT
				push 0
				push DLL_PROCESS_ATTACH // ставим флаг что подгрузили DLL
				push retadr
				call eax // передадим управление на точку входа в DLL 
			}
			hmod = (HMODULE)retadr;
		}
	}
}

SleshLibrary::~SleshLibrary(void) {
	free();
}

void SleshLibrary::getLastError(string &str, LPCSTR lpszFunction) {
	LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR) &lpMsgBuf,
        0, NULL );

	str.assign(lpszFunction);
	str += " failed with error: ";
	str += (LPSTR)lpMsgBuf;

    LocalFree(lpMsgBuf);
}

// обработка релоков
void SleshLibrary::progressReloc(ULONG retadr) {
	ULONG PE;
	ULONG IB;
	ULONG cnt;
	ULONG x;
	ULONG Delta;
	PFIXREC fixrec;
	USHORT fixtype;
	USHORT fixoffset;
  
	PE = *(ULONG*)(retadr + 0x3C) + retadr; // получаем адрес PE заголовка
	IB = *(ULONG*)(PE + 0x34); // IMAGE BASE 
	// Если совпадает с загруженным адресом, то фиксить не нужно ничего
	if (retadr == IB) return; 
	Delta = retadr - IB; // выцесляем дельта смещение.
	
	if (!*(ULONG*)(PE + 0xA0)) return; // если нет релоков то выходим
	// получаем адрес таблицы релоков
	fixrec = (PFIXREC)(*(ULONG*)(PE + 0xA0) + retadr);
	while (fixrec->BlockSize) { // если таблица не пуста
		cnt = (fixrec->BlockSize - 8) >> 1; // вычеслим кол-во элементов
		for (x = 0; x < cnt; x++) {
			fixtype = (fixrec->TOR[x]) >> 12; // типа фиксации
			// офсет внутри 4-х килобайтового блока
			fixoffset = (fixrec->TOR[x]) % 4096; 
			if (!fixtype) continue; // если 0, то фиксация не нужна
			if (fixtype == 3) { // если 3, то прибавить дельта смещение
				*(ULONG*)(retadr+fixoffset+fixrec->PageRVA) =
					*(ULONG*)(retadr+fixoffset+fixrec->PageRVA) + Delta;
			} else {
				// все остальные случае вызовут ошибку (хотя их и не будет теоретически)
				throw DllException("Unexpected situation detected");
			}
		}
		 // следующая таблица реловок
		fixrec = (PFIXREC)((ULONG)fixrec + fixrec->BlockSize);
	} 
}

void SleshLibrary::progressImport(ULONG retadr) {
	string error;
	ULONG PE;
	HMODULE lib;
	PIMPORT_TABLE ImportTable;
	PADDRESS_TABLE AddressTable;
	ULONG IAT_Index;
	ULONG RVA;
	ULONG addr;

	PE = *(ULONG*)(retadr + 0x3C) + retadr; // адрес PE заголовка
	if (!*(ULONG*)(PE + 0x80)) return; // если нет импорта то выходим
	// адрес таблицыы импорта
	ImportTable = (PIMPORT_TABLE)(*(ULONG*)(PE + 0x80) + retadr); 
	
	// пока есть DLL откуда нужно импортировать функции
	while (ImportTable->NameRVA) { 
		// проверим что DLL была ранее загружена
		lib = GetModuleHandleA((char*)(ImportTable->NameRVA + retadr)); 
		if ( !lib ) { // если не загружена была, то загрузим её.
			lib = LoadLibraryA((char*)(ImportTable->NameRVA + retadr));
		}
		if ( ! lib ) {
			getLastError(error, "LoadLibraryA");
			error += ": [";
			error += (char*)(ImportTable->NameRVA + retadr);
			error += "]";
			throw DllException(error.c_str());
		}

		if (ImportTable->LookUp) { 
			// Если импорт идет через LookUp
			RVA = ImportTable->LookUp + retadr;
		} else {
			// если через таблицу адресов импорта
			RVA = ImportTable->AddresTableRVA + retadr;
		}
		IAT_Index = 0;
		while ( *(ULONG*)RVA ) { // если есть ссылка на таблицу имен
			// получаем адрес структуры где хранится HINT NAME
			AddressTable = (PADDRESS_TABLE)(*(ULONG*)RVA + retadr);
			if ( (ULONG)AddressTable < 0x80000000 && AddressTable->Name[0] ) {
				 // если импорт по имени
				// найдем адрес
				addr = (ULONG)GetProcAddress(lib, AddressTable->Name); 
			} else {
				// если импорт по ординалу
				addr = (ULONG)GetProcAddress(lib, (char*)((USHORT)AddressTable));
			}
			if ( ImportTable->AddresTableRVA ) {
				// если есть IAT то сохраним в неё найденный адрес
				*(ULONG*)(ImportTable->AddresTableRVA + retadr + IAT_Index) = addr;
			} else {
				// иначе сохраним туда откуда брали
				*(ULONG*)RVA = addr;
			}
			RVA += 4; // сделающий элемент
			IAT_Index += 4;
		}
		// следующая таблица
		ImportTable = (PIMPORT_TABLE)((ULONG)ImportTable+sizeof(IMPORT_TABLE)); 
	}
}

void SleshLibrary::free() {
	PIMAGE_DOS_HEADER DosHeader;
	PIMAGE_NT_HEADERS PeHeader;
	ULONG EP;

	if ( hmod ) {
		DosHeader = (PIMAGE_DOS_HEADER)hmod; //  DOS заголово
		PeHeader = (PIMAGE_NT_HEADERS)(DosHeader->e_lfanew + (ULONG)hmod);// PE заголовок
		EP = PeHeader->OptionalHeader.AddressOfEntryPoint + (ULONG)hmod; // Точка входа
		__asm {
			push 0
			push DLL_PROCESS_DETACH //  флаг выгрузки DLL
			push hmod
			call EP // передаем управление на точку входа в DLL
		}
		VirtualFree(hmod, 0, MEM_RELEASE); // очищаем память
		hmod = NULL;
	}
}

FARPROC SleshLibrary::getProcAddress(const char *lpProcName) {
	ULONG PE;
	PIMAGE_EXPORT_DIRECTORY ED;
	PULONG NamePointerRVA;
	PUSHORT OrdinalTableRVA;
	PULONG AddressTableRVA;

	ULONG ret = 0;
	USHORT hint = 0;
	USHORT index;
	char * name;
	ULONG addr;
	ULONG CNT_FUNC;
	
	if ( (ULONG)lpProcName <= 0xFFFF ) { // если импорт по ординалу
		hint = (USHORT)lpProcName; // запишем наш ординал
	}

	if ( ! hmod ) {
		throw DllException("Library not loaded");
	}
	PE = *(ULONG*)((ULONG)hmod + 0x3C) + (ULONG)hmod;// адрес PE заголовка
	// адрес таблицы экспорта
	ED = (PIMAGE_EXPORT_DIRECTORY)(*(ULONG*)((ULONG)PE + 0x78) + (ULONG)hmod);

	// адрес таблицы имен
	NamePointerRVA = (ULONG*)(ED->AddressOfNames + (ULONG)hmod);
	// адрес таблицы ординалов
	OrdinalTableRVA	= (USHORT*)(ED->AddressOfNameOrdinals + (ULONG)hmod);
	// адрес таблицы адерсов
	AddressTableRVA = (ULONG*)(ED->AddressOfFunctions + (ULONG)hmod);
	
	// вычесляем наибольшее значение - кол-во функций
	if (ED->NumberOfNames > ED->NumberOfFunctions)  {
		CNT_FUNC = ED->NumberOfNames;
	} else {
		CNT_FUNC = ED->NumberOfFunctions;
	}

	// пройдемся по всем функциям
	for (USHORT x = 0; x < CNT_FUNC; x++) {
		if (x < ED->NumberOfFunctions) { // если есть имя у функции
			name = (char*)(NamePointerRVA[x] + (ULONG)hmod); // запомним имя
			index = OrdinalTableRVA[x]; // запомним ординал
		} else { // если имени нет
			name = 0; // имени нет
			index = x; // ординал = текущей позиции
		}

		// вычесляем адрес функции 
		addr = AddressTableRVA[index] + (ULONG)hmod;
		if ((hint == index + ED->Base)|| // если это наш ординал
			(name && !strcmp(name, lpProcName))) // если есть имя и оно наше
		{
			ret = addr; // нашли адрес
			break; // прекратим обход экспорта
		}
	}
	if ( ! ret ) {
		string error = "Proc not found: ";
		error += lpProcName;
		throw DllException(error.c_str());
	}
	return (FARPROC)ret; // вернем адрес 
}

	} // end namespace core
} // end namespace aquila
