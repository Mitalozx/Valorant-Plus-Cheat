#include "blabla/include.h"
#include "driver/driver.h"
#include "sdk/cheats.h"
#include "blabla/skStr.h"
#include "blabla/download.h"
#include <locale>
#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <winerror.h>
#include <ntstatus.h>
#include <bcrypt.h>
#include <wininet.h>
#include <xstring>
#include <vector>
#include <fstream>
#include <chrono>
#include <codecvt>
#include <nlohmann/json.hpp>
#include "blabla/protect.h"
#include <Wininet.h>
#include <string>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "bcrypt.lib")
#pragma comment(lib, "libcurl.lib")

#include "auth.hpp"

#pragma optimize("", off)

using namespace std;
namespace fs = std::filesystem;

using namespace KeyAuth;

auto name = ("World");
auto ownerid = ("GBkUplZ61P");
auto secret = ("17ae80a24c57b9bf0d6ea0563bcdeb9e0896fb431037ae82fe66e6e0f1a8b0ad");
auto version = ("1.0");
auto url = ("https://keyauth.win/api/1.2/");
api KeyAuthApp(name, ownerid, secret, version, url);

DWORD GetProcessID(const std::wstring processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE)
    {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}


auto get_process_wnd(uint32_t pid) -> HWND
{
    std::pair<HWND, uint32_t> params = { 0, pid };
    BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
        auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
        uint32_t processId = 0;

        if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
            SetLastError((uint32_t)-1);
            pParams->first = hwnd;
            return FALSE;
        }

        return TRUE;

        }, (LPARAM)&params);

    if (!bResult && GetLastError() == -1 && params.first)
        return params.first;

    return NULL;
}


std::string generateRandomName(int length) {
    std::string name;
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < length; ++i) {
        int index = rand() % (sizeof(charset) - 1);
        name += charset[index];
    }

    return name;
}


std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);
size_t wclbcks(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}


std::string encrypt(const std::string& input, const std::string& key)
{
    std::string output = input;
    for (size_t i = 0; i < input.length(); ++i)
    {
        output[i] = input[i] ^ key[i % key.length()];
    }
    return output;
}

std::string decrypt(const std::string& input, const std::string& key)
{
    std::string output = input;
    size_t length = input.length();
    size_t keyLength = key.length();

    for (size_t i = 0; i < length; ++i) {
        output[i] = input[i] ^ key[i % keyLength];
    }

    return output;
}

void cheat()
{
    std::string activecheat = "";
    std::string notfounddrver = "[-] Driver Error. Restart Your Computer..";
    std::string ntfoundgame = "";

    if (mem::lexemvefind_driver()) {
        system("cls");
    }
    else {
        system("cls");
        system("color c");
        for (char& c : notfounddrver) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        Sleep(3000);
        exit(0);
    }

    if (mem::lexemvefind_process(L"VALORANT-Win64-Shipping.exe")) {
        lexemvevirtualaddy = get_guarded_reg();
        check::guard = lexemvevirtualaddy;
        system("cls");
        for (char& c : activecheat) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        LAGMMEEE::LASTRTC();
    }
    else {
        system("cls");
        system("color c");
        for (char& c : ntfoundgame) {
            std::cout << c;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        Sleep(2000);
        exit(0);
    }
}

bool SetClipboard(const std::string& data) {

    auto size = data.size() + 1;
    auto pGlobal = GlobalAlloc(GMEM_MOVEABLE, size);

    if (!pGlobal) {

        return false;
    }

    OpenClipboard(0);
    EmptyClipboard();

    auto pLock = GlobalLock(pGlobal);

    if (!pLock) {
        CloseClipboard();
        return false;
    }

    CopyMemory(pLock, data.c_str(), size);

    GlobalUnlock(pGlobal);

    SetClipboardData(CF_TEXT, pGlobal);

    CloseClipboard();

    GlobalFree(pGlobal);

    return true;
}

void setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

std::string random_string(const int len) {
    const std::string alpha_numeric("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890");

    std::default_random_engine generator{ std::random_device{}() };
    const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };
    string newstr;
    int pos;
    std::string str(len, 0);
    while (newstr.size() != 32)
    {
        pos = ((rand() % (str.size() + 1)));
        newstr += str.substr(pos, 1);
    }

    return str + " | Developer : unknown ";
}

int main(HWND, UINT, WPARAM, LPARAM);

int main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    SetConsoleTitleA(random_string(8).c_str());

    KeyAuthApp.init();

    system("cls");



    setcolor(2);

    printf("\n\n");
    printf("##########################################################\n");
    setcolor(15);
    printf("[                 Select an option:                      ]\n");
    setcolor(2);
    printf("##########################################################\n\n");

    setcolor(15);

    printf("[");

    setcolor(2);

    printf("+");

    setcolor(15);

    printf("]");

    setcolor(15);

    printf(" Status > Valorant Plus | ");

    setcolor(2);

    printf("Undetected.\n\n");

    setcolor(15);

    printf("[");

    setcolor(5);

    printf("1");

    setcolor(15);

    printf("]");

    setcolor(15);

    std::cout << XorStr(" Registration keyy\n\n");

    printf("[");

    setcolor(5);

    printf("+");

    setcolor(15);

    printf("]");

    setcolor(15);
    printf(" Select an option: ");

    int option;
    std::string username;
    std::string password;
    std::string key;

    std::cin >> option;
    switch (option)
    {
    case 1:
        system("cls");

        setcolor(5);

        printf("\n\n");
        printf("##########################################################\n");
        setcolor(15);
        printf("[                     Enter your key:                    ]\n");
        setcolor(5);
        printf("##########################################################\n\n");
        setcolor(15);
        std::cout << XorStr("\n[");
        setcolor(5);
        std::cout << XorStr("+");
        setcolor(15);
        std::cout << XorStr("] Key: ");
        std::cin >> key;
        KeyAuthApp.license(key);
        break;
    default:
         std::cout << ("\n\n Status: Failure: Invalid Selection");
        Sleep(3000);
        exit(1);
    }  if (!KeyAuthApp.data.success)
    {
         std::cout << ("\n Status: ") << KeyAuthApp.data.message;
        Sleep(1500);
        exit(1);
    }

    Sleep(3500);

    system("cls");

    if (mem::lexemvefind_driver()) {
        goto Func;
    }
    else {
        lexemvemmap_driver();
        Sleep(1);
        goto Func;
    }

Func:
    system("cls");

    std::cout << "\n Open V4L0R4NT and Press F1 in Lobby..";

    while (true) {

        if (GetAsyncKeyState(VK_F1)) 
        {

            break;
        }
    }

    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window, 0);

    mem::lexemvefind_process(L"VALORANT-Win64-Shipping.exe");

    if (mem::lexemveprocess_id != 0)
    {
        MessageBoxA(0, "If the overlay doesn't appear or freezes... Open Valorant Plus again to update!", "WARNING", MB_OK | MB_ICONINFORMATION);
        Sleep(5000);
        cheat();
    }
}



#pragma optimize("", on)