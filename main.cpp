#include <windows.h>
#include <stdio.h>

bool isptr(unsigned char* b)
{
    DWORD val = *(DWORD*)b;
    return val > 0x10000 && val < 0x7FFFFFFF;
}

int main(int argc, char** argv)
{
    FILE* f = 0;
    fopen_s(&f, "input.bin", "rb");
    if (!f) return 1;

    fseek(f, 0, 2);
    int len = ftell(f);
    fseek(f, 0, 0);

    unsigned char* buf = (unsigned char*)malloc(len);
    fread(buf, 1, len, f);
    fclose(f);

    for (int i = 0; i < len;)
    {
        if (i + 4 <= len && isptr(&buf[i]))
        {
            printf("? ? ? ? ");
            i += 4;
        }
        else
        {
            printf("%02X ", buf[i]);
            i++;
        }
    }

    free(buf);
    return 0;
}
