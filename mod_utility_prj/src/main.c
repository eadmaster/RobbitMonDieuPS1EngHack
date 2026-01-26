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


void apply_patches_from_csv(const char *csv_path)
{
    char addr_buf[CSV_FIELD_LEN / 2];
    char str_buf[CSV_FIELD_LEN * 2];

    int fd = open_syscall(csv_path, 1);  // bit0 = 1 = read-only
    if (fd < 0)
        return;

    //int row = 0;

        /*
    while (1)
    {
        int ch;
        int phase = 0;
        int pos_addr = 0;
        int pos_str  = 0;

        // Read one line
        while (1)
        {
            ch = getc_syscall(fd);
            if (ch == -1)
                break;  // EOF
            //if ( read_syscall(fd, &ch, 1) <= 0 )
            //    return;

            if (ch == ',' && phase == 0)
            {
                phase = 1;
                continue;
            }

            if (ch == '\n')
                break;

            if (phase == 0)
            {
                // parsing address
                if (pos_addr < CSV_FIELD_LEN - 1)
                    addr_buf[pos_addr++] = (char)ch;
            }
            else
            {
                // parsing text string
                if (pos_str < CSV_FIELD_LEN - 1)
                    str_buf[pos_str++] = (char)ch;
            }
        }

        if (ch == -1) break; // EOF

        addr_buf[pos_addr] = '\0';
        str_buf[pos_str]   = '\0';

        // Patch memory directly
        volatile unsigned char *addr = (volatile unsigned char *)parse_hex(addr_buf);
        apply_patch_single(addr, str_buf);
        
        // reset
        phase = 0;
        pos_addr = 0;
        pos_str  = 0;
        
        //row++;
    }*/

    close_syscall(fd);
    return;
}

void ModMain(void) {
    //printf_syscall("Hello World!\n");
    
    // main menu
    volatile unsigned short* test_ptr_16bit = (volatile unsigned short*)0x000B728C;
    if(*test_ptr_16bit==0xCD82)  // TODO: more reliable test
    {
        apply_patches_from_mem(text_patches_main_menu, sizeof(text_patches_main_menu) / sizeof(text_patches_main_menu[0]));
    }
    
    // ingame
    char CSV_FILENAME[] = "cdrom:DUMMY.DAT";
    test_ptr_16bit = (volatile unsigned short*)0x000a4ce0;
    if(*test_ptr_16bit==0xCC8D)  // TODO: more reliable test
    {
        //apply_patches_from_csv("cdrom:DUMMY.DAT");
        apply_patches_from_csv(CSV_FILENAME);
    }
    

    return;
}

