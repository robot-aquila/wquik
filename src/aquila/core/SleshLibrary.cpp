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

#define MAX_SECTIONS 10  // ������������ ���-�� ������ � �����

typedef unsigned long ULONG, *PULONG;
typedef unsigned short USHORT, *PUSHORT;

#pragma warning(disable: 4200)
// ��������� ��� �������
typedef struct _FIXREC {
	ULONG	PageRVA;
	ULONG	BlockSize;
	USHORT	TOR[];
} TFIXREC,*PFIXREC;

// ��������� ������� �������
typedef struct _IMPORT_TABLE
{
	ULONG LookUp;
	ULONG TimeStamp;
	ULONG ForwardChain;
	ULONG NameRVA;
	ULONG AddresTableRVA;
} IMPORT_TABLE, *PIMPORT_TABLE;

#pragma pack(1) // ��������� ����������
// ��������� ������� �������
typedef struct _ADDRESS_TABLE {
	USHORT Hint;
	char Name[];
} ADDRESS_TABLE, *PADDRESS_TABLE;
#pragma pack() // ��������� ����������
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

	// ������� ���� �� ������
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

	// ������� DOS ���������
	if ( ReadFile(hFile, &DosHeader, sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 ) {
		getLastError(error, "ReadFile");
		CloseHandle(hFile);
		throw DllException(error.c_str());
	}

	if (DosHeader.e_magic == IMAGE_DOS_SIGNATURE) { // �������� ���������
		// ���� ���� �������� ������ ����� DOS ���������� � PE 
		// �� ������� ��. � MS ������������ ��� ����� Rich ������
		if (sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew) {
			if ( ReadFile(hFile, &tmp[0], DosHeader.e_lfanew -
				sizeof(IMAGE_DOS_HEADER), &rb, 0) == 0 )
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
		}
		// ��������� ��������� � ����� �� PE ���������
		if ( SetFilePointer(hFile, DosHeader.e_lfanew, 0, FILE_BEGIN) ==
			INVALID_SET_FILE_POINTER )
		{
			getLastError(error, "SetFilePointer");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}
		// ������� ���������
		if ( ReadFile(hFile, &PeHeader, sizeof(IMAGE_NT_HEADERS), &rb, 0) == 0 ) {
			getLastError(error, "ReadFile");
			CloseHandle(hFile);
			throw DllException(error.c_str());
		}

		if ( PeHeader.Signature == IMAGE_NT_SIGNATURE ) { // �������� ���������
			// ������� 10 ������
			if ( ReadFile(hFile, &Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections, &rb, 0) == 0 ) 
			{
				getLastError(error, "ReadFile");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			// ������� ������ �������, ������� ������� � SIZE OF BASE
			retadr = (ULONG)VirtualAlloc(0, PeHeader.OptionalHeader.SizeOfImage,
				MEM_COMMIT | MEM_RESERVE | MEM_TOP_DOWN, PAGE_EXECUTE_READWRITE);
			if ( retadr == NULL ) {
				getLastError(error, "VirtualAlloc");
				CloseHandle(hFile);
				throw DllException(error.c_str());
			}
			
			// ��������� ���� DOS ���������
			memcpy((void*) retadr, &DosHeader, sizeof(IMAGE_DOS_HEADER));
			// ��������� ���� PE ���������
			memcpy((void*)(retadr + DosHeader.e_lfanew), &PeHeader,
				sizeof(IMAGE_NT_HEADERS));
			// ��������� ���� ������� ������
			memcpy((void*)(retadr + DosHeader.e_lfanew + sizeof(IMAGE_NT_HEADERS)),
				&Section[0], sizeof(IMAGE_SECTION_HEADER) *
				PeHeader.FileHeader.NumberOfSections);
			// ���� ���� Rich ������ �� � �� ���� ���������
			if ( sizeof(IMAGE_DOS_HEADER) < DosHeader.e_lfanew )  {
				memcpy((void*)(retadr + sizeof(IMAGE_DOS_HEADER)), &tmp[0],
					DosHeader.e_lfanew - sizeof(IMAGE_DOS_HEADER));
			}
			// ���������� ������ ������
			for ( int i = 0; i < PeHeader.FileHeader.NumberOfSections; i++ ){
				// ��������� ��������� � ����� �� ������ ������ � �����
				if ( SetFilePointer(hFile, Section[i].PointerToRawData, 0, FILE_BEGIN) ==
					INVALID_SET_FILE_POINTER )
				{
					getLastError(error, "SetFilePointer");
					CloseHandle(hFile);
					VirtualFree((LPVOID)retadr, 0, MEM_RELEASE); // ������� ������
					throw DllException(error.c_str());
				}
				// ������� �� ������
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

			// ���������� ������
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
				push DLL_PROCESS_ATTACH // ������ ���� ��� ���������� DLL
				push retadr
				call eax // ��������� ���������� �� ����� ����� � DLL 
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

// ��������� �������
void SleshLibrary::progressReloc(ULONG retadr) {
	ULONG PE;
	ULONG IB;
	ULONG cnt;
	ULONG x;
	ULONG Delta;
	PFIXREC fixrec;
	USHORT fixtype;
	USHORT fixoffset;
  
	PE = *(ULONG*)(retadr + 0x3C) + retadr; // �������� ����� PE ���������
	IB = *(ULONG*)(PE + 0x34); // IMAGE BASE 
	// ���� ��������� � ����������� �������, �� ������� �� ����� ������
	if (retadr == IB) return; 
	Delta = retadr - IB; // ��������� ������ ��������.
	
	if (!*(ULONG*)(PE + 0xA0)) return; // ���� ��� ������� �� �������
	// �������� ����� ������� �������
	fixrec = (PFIXREC)(*(ULONG*)(PE + 0xA0) + retadr);
	while (fixrec->BlockSize) { // ���� ������� �� �����
		cnt = (fixrec->BlockSize - 8) >> 1; // �������� ���-�� ���������
		for (x = 0; x < cnt; x++) {
			fixtype = (fixrec->TOR[x]) >> 12; // ���� ��������
			// ����� ������ 4-� ������������� �����
			fixoffset = (fixrec->TOR[x]) % 4096; 
			if (!fixtype) continue; // ���� 0, �� �������� �� �����
			if (fixtype == 3) { // ���� 3, �� ��������� ������ ��������
				*(ULONG*)(retadr+fixoffset+fixrec->PageRVA) =
					*(ULONG*)(retadr+fixoffset+fixrec->PageRVA) + Delta;
			} else {
				// ��� ��������� ������ ������� ������ (���� �� � �� ����� ������������)
				throw DllException("Unexpected situation detected");
			}
		}
		 // ��������� ������� �������
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

	PE = *(ULONG*)(retadr + 0x3C) + retadr; // ����� PE ���������
	if (!*(ULONG*)(PE + 0x80)) return; // ���� ��� ������� �� �������
	// ����� �������� �������
	ImportTable = (PIMPORT_TABLE)(*(ULONG*)(PE + 0x80) + retadr); 
	
	// ���� ���� DLL ������ ����� ������������� �������
	while (ImportTable->NameRVA) { 
		// �������� ��� DLL ���� ����� ���������
		lib = GetModuleHandleA((char*)(ImportTable->NameRVA + retadr)); 
		if ( !lib ) { // ���� �� ��������� ����, �� �������� �.
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
			// ���� ������ ���� ����� LookUp
			RVA = ImportTable->LookUp + retadr;
		} else {
			// ���� ����� ������� ������� �������
			RVA = ImportTable->AddresTableRVA + retadr;
		}
		IAT_Index = 0;
		while ( *(ULONG*)RVA ) { // ���� ���� ������ �� ������� ����
			// �������� ����� ��������� ��� �������� HINT NAME
			AddressTable = (PADDRESS_TABLE)(*(ULONG*)RVA + retadr);
			if ( (ULONG)AddressTable < 0x80000000 && AddressTable->Name[0] ) {
				 // ���� ������ �� �����
				// ������ �����
				addr = (ULONG)GetProcAddress(lib, AddressTable->Name); 
			} else {
				// ���� ������ �� ��������
				addr = (ULONG)GetProcAddress(lib, (char*)((USHORT)AddressTable));
			}
			if ( ImportTable->AddresTableRVA ) {
				// ���� ���� IAT �� �������� � �� ��������� �����
				*(ULONG*)(ImportTable->AddresTableRVA + retadr + IAT_Index) = addr;
			} else {
				// ����� �������� ���� ������ �����
				*(ULONG*)RVA = addr;
			}
			RVA += 4; // ��������� �������
			IAT_Index += 4;
		}
		// ��������� �������
		ImportTable = (PIMPORT_TABLE)((ULONG)ImportTable+sizeof(IMPORT_TABLE)); 
	}
}

void SleshLibrary::free() {
	PIMAGE_DOS_HEADER DosHeader;
	PIMAGE_NT_HEADERS PeHeader;
	ULONG EP;

	if ( hmod ) {
		DosHeader = (PIMAGE_DOS_HEADER)hmod; //  DOS ��������
		PeHeader = (PIMAGE_NT_HEADERS)(DosHeader->e_lfanew + (ULONG)hmod);// PE ���������
		EP = PeHeader->OptionalHeader.AddressOfEntryPoint + (ULONG)hmod; // ����� �����
		__asm {
			push 0
			push DLL_PROCESS_DETACH //  ���� �������� DLL
			push hmod
			call EP // �������� ���������� �� ����� ����� � DLL
		}
		VirtualFree(hmod, 0, MEM_RELEASE); // ������� ������
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
	
	if ( (ULONG)lpProcName <= 0xFFFF ) { // ���� ������ �� ��������
		hint = (USHORT)lpProcName; // ������� ��� �������
	}

	if ( ! hmod ) {
		throw DllException("Library not loaded");
	}
	PE = *(ULONG*)((ULONG)hmod + 0x3C) + (ULONG)hmod;// ����� PE ���������
	// ����� ������� ��������
	ED = (PIMAGE_EXPORT_DIRECTORY)(*(ULONG*)((ULONG)PE + 0x78) + (ULONG)hmod);

	// ����� ������� ����
	NamePointerRVA = (ULONG*)(ED->AddressOfNames + (ULONG)hmod);
	// ����� ������� ���������
	OrdinalTableRVA	= (USHORT*)(ED->AddressOfNameOrdinals + (ULONG)hmod);
	// ����� ������� �������
	AddressTableRVA = (ULONG*)(ED->AddressOfFunctions + (ULONG)hmod);
	
	// ��������� ���������� �������� - ���-�� �������
	if (ED->NumberOfNames > ED->NumberOfFunctions)  {
		CNT_FUNC = ED->NumberOfNames;
	} else {
		CNT_FUNC = ED->NumberOfFunctions;
	}

	// ��������� �� ���� ��������
	for (USHORT x = 0; x < CNT_FUNC; x++) {
		if (x < ED->NumberOfFunctions) { // ���� ���� ��� � �������
			name = (char*)(NamePointerRVA[x] + (ULONG)hmod); // �������� ���
			index = OrdinalTableRVA[x]; // �������� �������
		} else { // ���� ����� ���
			name = 0; // ����� ���
			index = x; // ������� = ������� �������
		}

		// ��������� ����� ������� 
		addr = AddressTableRVA[index] + (ULONG)hmod;
		if ((hint == index + ED->Base)|| // ���� ��� ��� �������
			(name && !strcmp(name, lpProcName))) // ���� ���� ��� � ��� ����
		{
			ret = addr; // ����� �����
			break; // ��������� ����� ��������
		}
	}
	if ( ! ret ) {
		string error = "Proc not found: ";
		error += lpProcName;
		throw DllException(error.c_str());
	}
	return (FARPROC)ret; // ������ ����� 
}

	} // end namespace core
} // end namespace aquila
