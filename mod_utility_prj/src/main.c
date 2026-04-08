#include <types.h>
#include <symbols.h>
#include <syscalls.h>


typedef struct
{
    volatile unsigned char *addr;
    const char *ascii;
} TextPatch;


static const TextPatch text_patches_main_menu[] =
{
    //{ (volatile unsigned char*)0x000B728C, "Begin" },  // はじめから
    //{ (volatile unsigned char*)0x000b7280, "Continue  " },  // つづきから
    { (volatile unsigned char*)0x000b7278, "Load  " },  // ロード
    { (volatile unsigned char*)0x000b7268, "Settings    " },  // セッティング
    { (volatile unsigned char*)0x000b725C, "Credits " },  // あもいで
    { (volatile unsigned char*)0x001c4cc6, "Start from the\xFF\x81" "beginning    " },  // ゲームを最初から℃nめます
    { (volatile unsigned char*)0x001c4f76, "Load save game.           " },  //  データのロードを″sいます。
    { (volatile unsigned char*)0x001c4f9a, "Change the game\xFF\x81" "settings             " },  //  ゲームに関する♀e種設定を行います。
    { (volatile unsigned char*)0x000b7180, "Resident Memories" },
    { (volatile unsigned char*)0x000b7190, "Scrap" },
    { (volatile unsigned char*)0x000b719c, "Work Card" },
    { (volatile unsigned char*)0x000b71c0, "Reset Defaults" },
    { (volatile unsigned char*)0x000b71d0, "Move Camera" },
    { (volatile unsigned char*)0x000b71e8, "Special       " },
    { (volatile unsigned char*)0x000b71e0, "Drop  " },
    { (volatile unsigned char*)0x000b71f4, "Jump    " },
    { (volatile unsigned char*)0x000b7200, "Punch  " },
    { (volatile unsigned char*)0x000b7218, "Mono    " },
    { (volatile unsigned char*)0x000b7224, "Stereo  " },
    { (volatile unsigned char*)0x000b7230, "Sound Type    " },
    { (volatile unsigned char*)0x000b7240, "Controls" },
    { (volatile unsigned char*)0x000b724c, "Sound        " },
    { (volatile unsigned char*)0x000b72a4, "Back  " },
    { (volatile unsigned char*)0x000b725c, "Memories" },
    { (volatile unsigned char*)0x000b7268, "Settings" },
    { (volatile unsigned char*)0x000b7280, "Continue  " },
    { (volatile unsigned char*)0x000b728c, "New Game  " },
    { (volatile unsigned char*)0x000b7298, "Apply" },
/*
 * 0x000b7180 住民おもいで
0x000b7190 スクラップ
0x000b719c 勤務カード
0x000b71c0 初期設定に戻す
0x000b71d0 視点移動許可
0x000b71e0 急降下
0x000b71e8 特殊兵器
0x000b71f4 ジャンプ
0x000b7200 パンチ
0x000b7218 モノラル
0x000b7224 ステレオ
0x000b7230 サウンドタイプ
0x000b7240 操作設定
0x000b724c サウンド設定
0x000b72a4 もどる
0x000b725c おもいで
0x000b7268 セッティング
0x000b7280 つづきから
0x000b728c はじめから
0x000b7298 申請する
*/
};


static void apply_patch_single(volatile unsigned char *addr, const char *ascii)
{
    volatile unsigned char *dst = (volatile unsigned char *)addr; // 8-bit R/W pointer
    const char *src = ascii;

    while (*src)
    {
        if (*dst == '\0' && *(dst + 1) != '\0')
            break; // overflow safety check

        *dst++ = *src++;
    }
    *dst = '\0';  // null-termination
}

void apply_patches_from_mem(const TextPatch *patches, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        apply_patch_single(patches[i].addr, patches[i].ascii);
    }
}


    #define CSV_FIELD_LEN  128

    static int hex_to_int(char c)
    {
        if (c >= '0' && c <= '9') return c - '0';
        if (c >= 'A' && c <= 'F') return c - 'A' + 10;
        if (c >= 'a' && c <= 'f') return c - 'a' + 10;
        return -1;
    }

    static unsigned int parse_hex(const char *s)
    {
        unsigned int value = 0;
        if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
            s += 2;

        while (*s)
        {
            int v = hex_to_int(*s);
            if (v < 0) break;
            value = (value << 4) | v;
            s++;
        }
        
        return value;
    }


void apply_patches_from_csv(const char *csv_contents)
{
    // Safety check just in case a null pointer is passed
    if (!csv_contents) return;

    char addr_buf[CSV_FIELD_LEN / 2];
    char str_buf[CSV_FIELD_LEN * 2];

    int cursor = 0; // Use a cursor to track our position in the buffer

    // Loop until we hit the null-terminator at the end of the buffer
    while (csv_contents[cursor] != '\0')
    {
        int phase = 0;
        int pos_addr = 0;
        int pos_str  = 0;
        int skip_line = 0; // Flag to ignore comments
        char ch;

        if (csv_contents[cursor] == ';') {
            skip_line = 1;
        }
        
        // Read one line
        while (1)
        {
            ch = csv_contents[cursor];

            if (ch == '\0') 
                break; // End of file/buffer

            cursor++; // Advance the cursor for the next read

            if (ch == '\r') 
                continue; // Skip carriage returns (Windows CRLF line endings)

            if (ch == '\n') 
                break; // End of line
                
            if (skip_line)
                continue;  // Comments

            // Switch from address phase to string phase on space
            if (ch == ' ' && phase == 0)
            {
                phase = 1;
                continue;
            }

            if (phase == 0)
            {
                // parsing address
                // Fixed bounds check to match the array size: (CSV_FIELD_LEN / 2)
                if (pos_addr < (CSV_FIELD_LEN / 2) - 1)
                    addr_buf[pos_addr++] = ch;
            }
            else
            {
                // check escape codes
                if (ch == '\\') {
                    // Peek at the next character
                    char next_ch = csv_contents[cursor];
                    if (next_ch == 'n') {
                        ch = '\n'; // Convert to actual newline byte (0x0A)
                        cursor++;  // Skip the 'n'
                    } else if (next_ch == '\\') {
                        ch = '\\'; // Support literal backslashes if needed
                        cursor++;
                    } /*else if (next_ch == '0') {
                        ch = '\0'; // Support literal backslashes if needed
                        cursor++;
                    }*/
                    // Add more escapes like \t or \" here if necessary
                }

                if (pos_str < (CSV_FIELD_LEN * 2) - 1)
                    str_buf[pos_str++] = ch;
            }
        }

        // Only apply the patch if we actually parsed an address 
        // (This prevents crashes on empty lines or trailing newlines)
        if (pos_addr > 0)
        {
            addr_buf[pos_addr] = '\0';
            str_buf[pos_str]   = '\0';

            // Patch memory directly
            volatile unsigned char *addr = (volatile unsigned char *)parse_hex(addr_buf);
            apply_patch_single(addr, str_buf);
        }

        // If we broke out of the inner loop due to EOF, break the outer loop too
        if (ch == '\0') 
            break; 
    }
}



// Minute:Second:Sector:Track format used by the CD-ROM hardware
typedef struct {
    unsigned char minute;
    unsigned char second;
    unsigned char sector;
    unsigned char track;
} DslLOC;

// File metadata structure returned by DsSearchFile
typedef struct {
    DslLOC pos;         // The LBA position (This goes into our reader)
    unsigned int size;  // File size in bytes
    char name[16];      // Filename
} DslFILE;


// Address: 8002a00c - Locates a file on the disc
typedef DslFILE* (*SearchFunc)(DslFILE*, char*);
SearchFunc Game_DsSearchFile = (SearchFunc)0x8002a00c;

// Address: 8002a910 - High-level blocking read (LBA, Sectors, Buffer)
// This is the "OBJ_904" function that handles DsRead and DsReadSync internally.
typedef int (*SafeReadFunc)(int, int, void*);
SafeReadFunc Game_SafeRead = (SafeReadFunc)0x8002a910;

#define CD_BUSY_FLAG (*(volatile int*)0x80038078)

#define Game_DsSearchFile ((DslFILE* (*)(DslFILE*, char*))0x8002a00c)
#define Game_DsRead       ((int (*)(DslLOC*, int, void*, int))0x80029afc)
#define Game_DsReadSync   ((int (*)(unsigned char*))0x80029eac)

typedef int (*VSyncFunc)(int);
VSyncFunc Game_VSync = (VSyncFunc)0x8002af7c;


void CsvLoad(char* filename) {
    DslFILE fileInfo;
    unsigned char syncResult;
    void* destination = (void*)0x801F8000; // Free High RAM near the stack
    
    /*
    int timeout = 0;
    while (CD_BUSY_FLAG != 0 && timeout < 100000) {
        timeout++; 
    }*/
    
    // Find file
    if (Game_DsSearchFile(&fileInfo, filename) == 0) return;

    //int lba = *(int*)(&fileInfo.pos);
    int sectors = (fileInfo.size + 2047) / 2048;

    // Start Asynchronous Read
    Game_DsRead(&fileInfo.pos, sectors, destination, 0x80);

    // We stay in this loop until the file is 100% in RAM.
    // By calling Game_VSync(0), we let the console's Interrupt 
    // Service Routine (ISR) handle the incoming CD data.
    int timeout = 0;
    while (Game_DsReadSync(&syncResult) > 0) {
        Game_VSync(0); 
        
        if (timeout++ > 3000) break; 
    }

    // NOW apply patches. 
    // The loop above ensured the CPU didn't move forward 
    // until the data was actually ready.
    apply_patches_from_csv(destination);
}


void ModMain(void) {
    //printf_syscall("Hello World!\n");
    
    // main menu
    volatile unsigned short* test_ptr_16bit = (volatile unsigned short*)0x000B728C;
    if(*test_ptr_16bit==0xCD82)  // TODO: more reliable test, fix freezing when going back to menu
    {
        apply_patches_from_mem(text_patches_main_menu, sizeof(text_patches_main_menu) / sizeof(text_patches_main_menu[0]));
        return;
    }

    // in map
    test_ptr_16bit = (volatile unsigned short*)0x000a4ce0;
    if(*test_ptr_16bit==0xCC8D)  // TODO: more reliable test
    {
        CsvLoad("\\MAP.CSV;1");
        return;
    }
    
    // ingame
    test_ptr_16bit = (volatile unsigned short*)0x000525a0;
    if(*test_ptr_16bit==0xE282)  // TODO: more reliable test
    {
        CsvLoad("\\INGAME.CSV;1");
        return;
    }
    
    return;
}

