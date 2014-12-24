#include "bigInt.h"
void BinaryWrite(BigInt *integer, char *FName)
{
    if(integer == NULL)
        return;
    std::ofstream out(FName, std::ios::out | std::ios::binary);
    if(!out.good())
    {
        throw std::invalid_argument("Error create file.\n");
        return;
    }
    if(!integer->size)
        out.write("0", 1);
    else
    {
    if(integer->Sign)
        out<<'-';
    if(integer->size)
        out.write(integer->Integer, integer->size);
    }
    out.close();
}
void TextWrite(BigInt *integer, char *FName)
{
    if(integer == NULL)
        return;
    std::ofstream out(FName, std::ios::out);
    if(!out.good())
    {
        throw std::invalid_argument("Error create file.\n");
        return;
    }
    if(!integer->size)
    out<<0;
    else
    {
        if(integer->Sign)
            out<<'-';
        int i = 0;
        while(i < integer->size)
        {
            out<<integer->Integer[i];
            i++;
        }
    }
    out.close();
}
int atoi(char ch)//Из символа в число
{
    int rez = ch - '0';
    if(rez >= 0 && rez <= 9)
        return rez;
    return -1;
}
char itoa(int i)//из цифры в символ
{
    if(i < 0)
        i = -i;
    char buf = '0' + i;
    if(buf >= '0' && buf <= '9')
        return buf;
    return 0;
}
char* shiftRight(char *integer, int p)//сдвиг строки на 1 разряд в право
{
    int i = 0, j = 0;
    while(integer[i] != '\0')
        i++;
    while(integer[j] == -51 )
        j++;
    size_t a = i - p, b = p;
    memcpy((void*)integer, (void*)(integer+p), a);
    memset((void*)(integer+(i-p)), '0', b);
    return integer;
}
char* divisionInTwo(char* integer)//Деление числа в строке на 2
{
    int size = 0, beg, it, cf = 0;
    while(integer[size] != '\0')
        size++;
    size_t a = size + 1;
    char *rez = (char*)malloc(a);
    beg = it = 0;
    if(beg < 0)
        return NULL;
    while(beg < size)
        {
        rez[it] = itoa((atoi(integer[beg]) + 10 * cf)/2);
        cf = atoi(integer[beg])%2;
        it++;
        beg++;
    }
    rez[it] = 0;
    return rez;
}
BigInt::BigInt()
{
    Integer = NULL;
    Sign = false;
    size = 0;
}
BigInt::BigInt(char *integer)
{
    Integer = NULL;
    Sign = false;
    size = 0;
    if(!integer || !strcmp(integer, ""))
        return;
    int anti_size = 0, i = 0;
    if(integer[0] == '-')
    {
        Sign = true;
        i++;
    }
    else if(integer[0] == '+')
        i++;
    else if(!isdigit(integer[0]))
    {
        throw std::invalid_argument("Error in input string. In first symbol.\n");
        return;
    }
    int j = i;
    while(integer[j] == '0')
        j++;
    anti_size += (j - i);
    while(isdigit(integer[i]))
    {
        size++;
        i++;
    }
    size = size - anti_size;
    if(!size)
        return;
    size_t a = size + 1, b = size;
    Integer = (char*)malloc(a);
    memcpy((void*)Integer, (void*)(integer+j), b);
    Integer[size] = 0;
}
BigInt::BigInt(int integer)
{
    Integer = NULL;
    Sign = false;
    size = 0;
    if(!integer)
        return;
    if(integer < 0)
        Sign = true;
    int int_buf = integer;
    do
        size++;
    while(int_buf /= 10);
    size_t a = size + 1;
    Integer = (char*)malloc(a);
    int i = size - 1;
    while(integer)
    {
        Integer[i] = itoa(integer%10);
        integer /= 10;
        i--;
    }
    Integer[size] = 0;
}
BigInt::BigInt(char *FName, bool Binary)
{
    Integer = NULL;
    Sign = false;
    size = 0;
    char buf;
    if(!Binary)
    {
        std::ifstream in(FName, std::ios::in);
        if(!in.good())
        {
            throw std::invalid_argument("Error open file.\n");
            return;
        }
        in.seekg(0, std::ios::end);
        size = in.tellg();
        in.seekg(0, std::ios::beg);
        in>>buf;
        if(buf == -52)
        {
            throw std::invalid_argument("Error: Empty file.\n");
            return;
        }
        else if(buf == '-')
        {
            Sign = true;
            size--;
            in>>buf;
        }
        else if(buf == '+')
        {
            size--;
            in>>buf;
        }
        else if(!isdigit(buf))
        {
            throw std::invalid_argument("Error in input file.\n");
            return;
        }
        int i = 0;
        while(buf == '0' && !in.eof())
        {
            in>>buf;
            size--;
        }
        if(size)
        {
            size_t a = size + 1;
            Integer = (char*)malloc(a);
            while(!in.eof())
            {
                if(!isdigit(buf))
                {
                    throw std::invalid_argument("Error in input string.\n");
                    free((void*)Integer);
                    size = 0;
                    Sign = false;
                    Integer = NULL;
                    return;
                }
                Integer[i] = buf;
                i++;
                in>>buf;
            }
            Integer[i] = 0;
        }
        in.close();
    }
    else
    {
        std::ifstream in(FName, std::ios::in | std::ios::binary);
        if(!in.good())
        {
            throw std::invalid_argument("Error open file.\n");
            return;
        }
        in.seekg(0, std::ios::end);
        size = in.tellg();
        in.seekg(0, std::ios::beg);
        in>>buf;
        if(buf == '-')
        {
            Sign = true;
            size--;
            in>>buf;
        }
        else if(buf == '+')
        {
            size--;
            in>>buf;
        }
        else if(!isdigit(buf))
        {
            throw std::invalid_argument("Error in input file.\n");
            return;
        }
        int i = 0;
        while(buf == '0' && !in.eof())
        {
            in>>buf;
            size--;
        }
        if(size)
        {
            size_t a = size + 1;
            Integer = (char*)malloc(a);
            while(!in.eof())
            {
                if(!isdigit(buf))
                {
                    throw std::invalid_argument("Error in input string.\n");
                    return;
                }
                Integer[i] = buf;
                i++;
                in>>buf;
            }
            Integer[i] = 0;
        }
        in.close();
    }
    size = strlen(Integer);
}
BigInt::BigInt(BigInt *integer)
{
    size = integer->size;
    Sign = integer->Sign;
    size_t a = size + 1, b = size;
    Integer = (char*)malloc(a);
    memcpy((void*)Integer, (void*)integer->Integer, b);
    Integer[size] = 0;
}
void BigInt::Update(char* integer)
{
    free(Integer);
    Integer = NULL;
    Sign = false;
    size = 0;
    int anti_size = 0, i = 0;
    if(!integer || integer[0] == '\0')
        return;
    if(integer[0] == '-')
    {
        Sign = true;
        i++;
    }
    else if(integer[0] == '+')
        i++;
    else if(!isdigit(integer[0]))
    {
        throw std::invalid_argument("Error in input string.\n");
        return;
    }
    int j = i;
    while(integer[j] == '0')
        j++;
    anti_size += (j - i);
    while(isdigit(integer[i]))
    {
        size++;
        i++;
    }
    size = size - anti_size;
    if(!size)
        return;
    size_t a = size + 1, b = size;
    Integer = (char*)malloc(a);
    memcpy(Integer, integer+j, b);
    Integer[size] = 0;
}
BigInt* BigInt::BinaryRead(char *FName)
{
    char buf;
    std::ifstream in(FName, std::ios::in | std::ios::binary);
    if(!in.good())
    {
        throw std::invalid_argument("Error open input binary file.\n");
        return NULL;
    }
    in.seekg(0, std::ios::end);
    size = in.tellg();
    in.seekg(0, std::ios::beg);
    if(!size)
    {
        throw std::invalid_argument("Error empty input binary file.\n");
        return NULL;
    }
    in>>buf;
    if(buf == '-')
    {
        Sign = true;
        size--;
        in>>buf;
    }
    else if(buf == '+')
    {
        Sign = false;
        size--;
        in>>buf;
    }
    else if(isdigit(buf))
        Sign = false;
    else
    {
        throw std::invalid_argument("Error in input binary file.\n");
        return NULL;
    }
    int i = 0;
    while(buf == '0' && !in.eof())
    {
        in>>buf;
        size--;
    }
    free((void*)Integer);
    size_t a =size + 1;
    Integer = (char*)malloc(a);
    while(!in.eof())
    {
        if(!isdigit(buf))
        {
            throw std::invalid_argument("Error in input string.\n");
            free((void*)Integer);
            Integer = NULL;
            return NULL;
        }
        Integer[i] = buf;
        i++;
        in>>buf;
    }
    Integer[i] = 0;
    in.close();
    return this;
}
BigInt* BigInt::TextRead(char *FName)
{
    char buf;
    std::ifstream in(FName, std::ios::in);
    if(!in.good())
    {
        throw std::invalid_argument("Error open input file.\n");
        return NULL;
    }
    in.seekg(0, std::ios::end);
    size = in.tellg();
    in.seekg(0, std::ios::beg);
    //size--;
    if(!size)
    {
        throw std::invalid_argument("Error empty input file.\n");
        return NULL;
    }
    in>>buf;
    if(buf == '-')
    {
        Sign = true;
        size--;
        in>>buf;
    }
    else if(buf == '+')
    {
        Sign = false;
        size--;
        in>>buf;
    }
    else if(isdigit(buf))
        Sign = false;
    else
    {
        throw std::invalid_argument("Error in input file.\n");
        return NULL;
    }
    int i = 0;
    while(buf == '0' && !in.eof())
    {
        in>>buf;
        size--;
    }
    free((void*)Integer);
    size_t a = size + 1;
    Integer = (char*)malloc(a);
    while(!in.eof())
    {
        if(!isdigit(buf))
        {
            throw std::invalid_argument("Error in input string.\n");
            return NULL;
        }
        Integer[i] = buf;
        i++;
        in>>buf;
    }
    Integer[i] = 0;
    in.close();
    return this;
}
void BigInt::BinaryWrite(char *FName)
{
    std::ofstream out(FName, std::ios::out | std::ios::binary);
    if(!out.good())
    {
        throw std::invalid_argument("Error create file.\n");
        return;
    }
    if(Sign)
        if(size)
            out<<'-';
    if(size)
        out.write(Integer, size);
    else
        out.write("0", 1);
    out.close();
}
void BigInt::TextWrite(char *FName)
{
    std::ofstream out(FName, std::ios::out);
    if(!out.good())
    {
        throw std::invalid_argument("Error create file.\n");
        return;
    }
    if(Sign)
        if(size)
            out<<'-';
    if(size)
    {
        int i = 0;
        while(i < size)
        {
            out<<Integer[i];
            i++;
        }
    }
    else
        out<<0;
        out.close();
}
BigInt* BigInt::Summary(BigInt* integer)
{
    if(!integer)
        return this;
    if(!integer->size)
        return this;
    if(!size)
        return integer;
    bool new_Sign;
    int great = 0;
    BigInt *new_int;
    char *new_Integer;
    int new_size;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    if(*this > *integer)
    {
        great = 1;
        new_size = size + 2;
        new_Sign = First_Sign;
    }
    else
    {
        great = 2;
        new_size = integer->size + 2;
        new_Sign = Second_Sign;
    }
    Sign = First_Sign;
    integer->Sign = Second_Sign;
    if(new_Sign)
        new_size++;
    size_t a = new_size + 1, b = new_size - 1;
    new_Integer = (char*)malloc(a);
    memset((void*)new_Integer, -51, b);
    new_Integer[new_size] = 0;
    if(Sign == integer->Sign)
    {
        int rez, i, j, k, CF=0, A, B;
        if(great == 1)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; i >= 0; i--, j--, k--)
        {
            if(great == 1)
            {
                A = atoi(Integer[j]);
                B = atoi(integer->Integer[i]);
            }
        else
        {
            A = atoi(integer->Integer[j]);
            B = atoi(Integer[i]);
        }
        rez = A + B + CF;
        CF = rez / 10;
        new_Integer[k] = itoa(rez%10);
        }
        for(; j >= 0; j--, k--)
        {
            if(great == 1) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            rez = A + CF;
            CF = rez / 10;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
            i++;
        new_int = new BigInt(new_Integer + i);
        free((void*)new_Integer);
        return new_int;
    }
    if(!Sign)//+(1)-(2) 1 - this
    {
        int rez, i, j, k, CF = 0, CFbuf, A, B;
        if(great == 1)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; i >= 0; i--, j--, k--)
        {
            if(great == 1)
            {
                A = atoi(Integer[j]);
                B = atoi(integer->Integer[i]);
            }
            else
            {
                A = atoi(integer->Integer[j]);
                B = atoi(Integer[i]);
            }
            CFbuf = 0;
            if (A < B)
            {
                A += 10;
                CFbuf++;
            }
            rez = A - B;
            if(CF)
            {
                if(!rez)
                {
                    rez += 10;
                    CFbuf++;
                }
                rez -= CF;
            }
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        for(; j >= 0; j--, k--)
        {
            if(great == 1) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            CFbuf = 0;
            rez = A;
            if(rez < CF)
            {
                rez += 10;
                CFbuf++;
            }
            rez -= CF;
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(new_Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
            i++;
        new_int = new BigInt(new_Integer + i);
        free((void*)new_Integer);
        return new_int;
    }
    else//+(2)-(1) 1 - this
    {
        int rez, CFbuf, i, j, k, CF = 0, A, B;
        if(great == 2)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; j >= 0; i--, j--, k--)
        {
            if(great == 2)
            {
                A = atoi(integer->Integer[i]);
                B = atoi(Integer[j]);
            }
            else
            {
                A = atoi(Integer[i]);
                B = atoi(integer->Integer[j]);
            }
            CFbuf = 0;
            if(A < B)
            {
                A += 10;
                CFbuf++;
            }
            rez = A - B;
            if(CF)
            {
                if(!rez)
                {
                    rez += 10;
                    CFbuf++;
                }
                rez -= CF;
            }
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        for(; i >= 0; i--, k--)
        {
            if(great == 2) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            CFbuf = 0;
            rez = A;
            if(rez < CF)
            {
                rez += 10;
                CFbuf++;
            }
            rez -= CF;
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(new_Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
        i++;
        new_int = new BigInt(new_Integer + i);
        free((void*)new_Integer);
        return new_int;
    }
    return NULL;
}
void BigInt::SummaryS(BigInt* integer)
{
    if(!integer)
        return;
    if(!integer->size)
        return;
    if(!size)
    {
        Sign = integer->Sign;
        size = integer->size;
        Update(integer->Integer);
        return;
    }
    bool new_Sign;
    int great = 0;
    char *new_Integer;
    int new_size;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    if(*this > *integer)
    {
        great = 1;
        new_size = size + 2;
        new_Sign = First_Sign;
        }
        else
        {
            great = 2;
            new_size = integer->size + 2;
            new_Sign = Second_Sign;
        }
        Sign = First_Sign;
        integer->Sign = Second_Sign;
        if(new_Sign)
            new_size++;
        size_t a = new_size + 1;
        new_Integer = (char*)malloc(a);
        memset(new_Integer, -51, new_size - 1);
        new_Integer[new_size] = 0;
    if(Sign == integer->Sign)
    {
        int rez, i, j, k, CF = 0, A, B;
        if(great == 1)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; i >= 0; i--, j--, k--)
        {
            if(great == 1)
            {
                A = atoi(Integer[j]);
                B = atoi(integer->Integer[i]);
            }
            else
            {
                A = atoi(integer->Integer[j]);
                B = atoi(Integer[i]);
            }
            rez = A + B + CF;
            CF = rez / 10;
            new_Integer[k] = itoa(rez%10);
        }
        for(; j >= 0; j--, k--)
        {
            if(great == 1) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            rez = A + CF;
            CF = rez / 10;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
            i++;
        Update(new_Integer+i);
        free((void*)new_Integer);
        return;
    }
    if(!Sign)//+(1)-(2) 1 - this
    {
        int rez, CFbuf, i, j, k, CF = 0, A, B;
        if(great == 1)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; i >= 0; i--, j--, k--)
        {
        if(great == 1)
        {
            A = atoi(Integer[j]);
            B = atoi(integer->Integer[i]);
        }
        else
        {
            A = atoi(integer->Integer[j]);
            B = atoi(Integer[i]);
        }
        CFbuf = 0;
        if (A < B)
        {
            A += 10;
            CFbuf++;
        }
        rez = A - B;
        if(CF)
        {
            if(!rez)
            {
                rez += 10;
                CFbuf++;
            }
            rez -= CF;
        }
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        for(; j >= 0; j--, k--)
        {
            if(great == 1) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            CFbuf = 0;
            rez = A;
            if(rez < CF)
            {
                rez += 10;
                CFbuf++;
            }
            rez -= CF;
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(new_Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
            i++;
        Update(new_Integer + i);
        free((void*)new_Integer);
        return;
    }
    else//+(2)-(1) 1 - this
    {
        int rez, CFbuf, i, j, k, CF = 0, A, B;
        if(great == 2)
        {
            i = integer->size - 1;
            j = size - 1;
        }
        else
        {
            j = integer->size - 1;
            i = size - 1;
        }
        for(k = new_size - 1; i >= 0; i--, j--, k--)
        {
            if(great == 2)
            {
                A = atoi(integer->Integer[i]);
                B = atoi(Integer[j]);
            }
            else
            {
                A = atoi(Integer[i]);
                B = atoi(integer->Integer[j]);
            }
            CFbuf = 0;
            if(A < B)
            {
                A += 10;
                CFbuf++;
            }
            rez = A - B;
            if(CF)
            {
                if(!rez)
                {
                    rez += 10;
                    CFbuf++;
                }
                rez -= CF;
            }
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        for(; j >= 0; j--, k--)
        {
            if(great ==2) A = atoi(Integer[j]);
            else A = atoi(integer->Integer[j]);
            CFbuf = 0;
            rez = A;
            if(rez < CF)
            {
                rez += 10;
                CFbuf++;
            }
            rez -= CF;
            CF = CFbuf;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k--] = '1';
        if(new_Sign)
            new_Integer[k--] = '-';
        i = 0;
        while(new_Integer[i] == -51)
            i++;
        Update(new_Integer + i);
        free((void*)new_Integer);
        return;
    }
}
BigInt* BigInt::Subtraction(BigInt* integer)
{
    if(!integer)
        return NULL;
    integer->Sign = !integer->Sign;
    BigInt* rez = Summary(integer);
    integer->Sign = !integer->Sign;
    return rez;
}
void BigInt::SubtractionS(BigInt* integer)
{
    if(!integer)
        return;
    integer->Sign = !integer->Sign;
    SummaryS(integer);
    integer->Sign = !integer->Sign;
}
BigInt* BigInt::Multiplication(BigInt* integer)
{
//второго числа нет
    if(!integer)
        return NULL;
    if(!integer->size || !size)
    {
        BigInt *zero = new BigInt(0);
        return zero;
    }
    bool new_Sign;
    BigInt *buf;
    char *new_Integer;
    BigInt *new_int, *cur;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    if(*this > *integer)
    {
        buf = new BigInt(integer);
        cur = new BigInt(this);
    }
    else
    {
        buf = new BigInt(this);
        cur = new BigInt(integer);
    }
    new_int = new BigInt(0);
    //////////////////////////////
    int rez, CF= 0, i, j, k, p, m, cur_size;
    for(i = cur->size - 1, p = 0; i >= 0; i--, p++)
    {
        int A = atoi(cur->Integer[i]);
        if(!A)
            continue;
        j = buf->size - 1;
        cur_size = buf->size + p + 1;
        size_t a = cur_size + 1, b = cur_size;
        new_Integer = (char*)malloc(a);
        memset((void*)new_Integer, -51, b);
        new_Integer[cur_size] = 0;
        for(k = cur_size-1; j >=0; j--, k--)
        {
            if(A == 1)
            {
                size_t c = buf->size;
                memcpy((void*)(new_Integer + (cur_size - buf->size)), (void*)buf->Integer, c);
                k = cur_size - buf->size + 1;
                break;
            }
            int B = atoi(buf->Integer[j]);
            if(!B)
            {
                new_Integer[k] = itoa(CF);
                CF = 0;
                continue;
            }
            rez = A*B + CF;
            CF = rez / 10;
            new_Integer[k] = itoa(rez%10);
        }
        if(CF)
            new_Integer[k++] = itoa(CF);
        new_Integer = shiftRight(new_Integer, p);
        m = 0;
        while(new_Integer[m] == -51)
            m++;
        BigInt *new_int_buf = new BigInt(new_Integer+m);
        new_int->SummaryS(new_int_buf);
        free((void*)new_int_buf->Integer);
        free((void*)new_Integer);
        CF = 0;
    }
    /////////////////
    new_int->Sign = new_Sign;
    Sign = First_Sign;
    integer->Sign = Second_Sign;
    free((void*)buf->Integer);
    free((void*)cur->Integer);
    return new_int;
}
void BigInt::MultiplicationS(BigInt* integer)
{
    //второго числа нет
    if(!integer)
        return;
    if(!integer->size)
    {
        Sign = false;
        size = 0;
        free((void*)Integer);
        Integer = NULL;
        return;
    }
    if(!size)
        return;
    bool new_Sign;
    BigInt *buf;
    char *new_Integer;
    BigInt *new_int, *cur;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    bool Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    if(*this > *integer)
    {
        buf = new BigInt(integer);
        cur = new BigInt(this);
    }
    else
    {
        buf = new BigInt(this);
        cur = new BigInt(integer);
    }
    new_int = new BigInt(0);
    //////////////////////////////
    int rez, CF = 0, i, j, k, p, m, cur_size;
    for(i = cur->size - 1, p = 0; i >= 0; i--, p++)
    {
        int A = atoi(cur->Integer[i]);
        if(!A)
            continue;
        j = buf->size - 1;
        cur_size = buf->size + p + 1;
        size_t a = cur_size + 1, b = cur_size;
        new_Integer = (char*)malloc(a);
        memset((void*)new_Integer, -51, b);
        new_Integer[cur_size] = 0;
        for(k = cur_size-1; j >=0; j--, k--)
        {
            if(A == 1)
            {
                size_t c = buf->size;
                memcpy((void*)(new_Integer + (cur_size - buf->size)), (void*)buf->Integer, c);
                k = cur_size - buf->size + 1;
                break;
            }
            int B = atoi(buf->Integer[j]);
            if(!B)
            {
                new_Integer[k] = itoa(CF);
                CF = 0;
                continue;
            }
            rez = A*B + CF;
            CF = rez / 10;
            new_Integer[k] = itoa(rez%10);
        } if(CF)
            new_Integer[k++] = itoa(CF);
        new_Integer = shiftRight(new_Integer, p);
        m = 0;
        while(new_Integer[m] == -51)
            m++;
        BigInt *new_int_buf = new BigInt(new_Integer+m);
        new_int->SummaryS(new_int_buf);
        CF = 0;
        free(new_Integer);
    }
    /////////////////
    integer->Sign = Second_Sign;
    Update(new_int->Integer);
    Sign = new_Sign;
    free((void*)buf->Integer);
    free((void*)cur->Integer);
    free((void*)new_int);
    return ;
}
BigInt* BigInt::DegreeToTen(BigInt* integer)
{
    BigInt *new_int = new BigInt(integer);
    new_int->MultiplicationS(new_int);
    new_int->MultiplicationS(new_int);
    new_int->MultiplicationS(integer);
    new_int->MultiplicationS(new_int);
    return new_int;
}
BigInt* BigInt::Degreed(BigInt* integer)
{
    if(!integer)
        return NULL;
    if(!integer->size)
    {
        BigInt *one = new BigInt(1);
        return one;
    }
    if(!size)
    {
        BigInt *zero = new BigInt(0);
        return zero;
    }
    bool new_sign;
    if(atoi(integer->Integer[size-1])%2)
        new_sign = Sign;
    else
        new_sign = true;
    BigInt** degreeNet = new BigInt*[integer->size], *new_int = new BigInt(1), *buf;
    degreeNet[0] = new BigInt(this);
    for(int i = 1; i < integer->size; i++)
        degreeNet[i] = DegreeToTen(degreeNet[i - 1]);
    for(int i = 0; i < integer->size; i++)
    {
        if(integer->Integer[i] == '0')
            continue;
        buf = new BigInt(degreeNet[integer->size - 1 - i]);
        for(int j = 1; j < atoi(integer->Integer[i]); j++)
            buf->MultiplicationS(degreeNet[integer->size - 1 - i]);
        new_int->MultiplicationS(buf);
        free((void*)buf);
    }
    free((void*)degreeNet);
    new_int->Sign = new_sign;
    return new_int;
}
void BigInt::DegreedS(BigInt *integer)
{
    if(!size)
        return;
    if(!integer)
        return;
    if(!integer->size)
    {
        size = 1;
        Sign = false;
        free((void*)Integer);
        Integer = new char[2];
        Integer[0] = 1;
        Integer[1] = '\0';
        return;
    }
    if(!atoi(integer->Integer[size-1])%2)
        Sign = true;
    BigInt** degreeNet = new BigInt*[integer->size], *new_int = new BigInt(1), *buf;
    degreeNet[0] = new BigInt(this);
    for(int i = 1; i < integer->size; i++)
        degreeNet[i] = DegreeToTen(degreeNet[i - 1]);
    for(int i = 0; i < integer->size; i++)
    {
        if(integer->Integer[i] == '0')
            continue;
        buf = new BigInt(degreeNet[integer->size - 1 - i]);
        for(int j = 1; j < atoi(integer->Integer[i]); j++)
            buf->MultiplicationS(degreeNet[integer->size - 1 - i]);
        new_int->MultiplicationS(buf);
        free((void*)buf);
    }
    free((void*)degreeNet);
    this->Update(new_int->Integer);
    free((void*)new_int);
}
BigInt* BigInt::Division(BigInt* integer)
{
    if(!integer)
        return NULL;
    if(!integer->size)
        return NULL;
    if(!size)
    {
        BigInt *zero = new BigInt(0);
        return zero;
    }
    bool new_Sign, end_div = false, good_div, good_devidend;
    BigInt *devidend, *devider, *new_int, *buf = new BigInt(0), *buf_devider, *req;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    if(size < integer->size)
        return this;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    devidend = new BigInt(this);
    devider = integer;
    new_int = new BigInt(0);
    buf_devider = new BigInt(divisionInTwo(devidend->Integer));
    while(!end_div)
    {
        buf = buf_devider->Multiplication(devider);
        if(*devidend >= *buf)
        good_div = true;
        else
        good_div = false;
        //
        if(good_div)
        {
            devidend->SubtractionS(buf);
            new_int->SummaryS(buf_devider);
        }
        //
        if(*devidend >= *buf) // true - можем разделить false - не можем
        good_devidend = true;
        else
        good_devidend = false;
        //
        if(!good_devidend)
        buf_devider->Update(divisionInTwo(buf_devider->Integer));
        //
        if(*devidend < *devider)
        end_div = true;
        else
        end_div = false;
    }
    integer->Sign = Second_Sign;
    Sign = First_Sign;
    new_int->Sign = new_Sign;
    req = new BigInt(devidend);
    free((void*)buf);
    free((void*)buf_devider);
    free((void*)devidend);
    free((void*)req);
    return new_int;
}
void BigInt::DivisionS(BigInt* integer)
{
    if(!integer)
        return;
    if(!integer->size || !size)
        return;
    if(size < integer->size)
        return;
    bool new_Sign, end_div = false, good_div, good_devidend;
    BigInt *devidend, *devider, *new_int, *buf = new BigInt(0), *buf_devider, *req;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    devidend = new BigInt(this);
    devider = integer;
    new_int = new BigInt(0);
    buf_devider = new BigInt(divisionInTwo(devidend->Integer));
    while(!end_div)
    {
        buf = buf_devider->Multiplication(devider);
        if(*devidend >= *buf)
            good_div = true;
        else
            good_div = false;
        //
        if(good_div)
        {
            devidend->SubtractionS(buf);
            new_int->SummaryS(buf_devider);
        }
    //
        if(*devidend >= *buf) // true - можем разделить false - не можем
            good_devidend = true;
        else
            good_devidend = false;
        //
        if(!good_devidend)
            buf_devider->Update(divisionInTwo(buf_devider->Integer));
        //
        if(*devidend < *devider)
            end_div = true;
        else
            end_div = false;
    }
    Update(new_int->Integer);
    Sign = new_Sign;
    req = new BigInt(devidend);
    new_int->Sign = new_Sign;
    free((void*)buf);
    free((void*)buf_devider);
    free((void*)devidend);
    free((void*)req);
    free((void*)new_int);
}
BigInt* BigInt::Modulation(BigInt* integer)
{
    if(!integer)
        return NULL;
    if(!integer->size || !size)
    {
        BigInt *zero = new BigInt(0);
        return zero;
    }
    bool new_Sign, end_div = false, good_div, good_devidend;
    BigInt *devidend, *devider, *new_int, *buf = new BigInt(0), *buf_devider, *req;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    if(size < integer->size)
        return this;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    devidend = new BigInt(this);
    devider = integer;
    new_int = new BigInt(0);
    buf_devider = new BigInt(divisionInTwo(devidend->Integer));
    while(!end_div)
    {
        buf = buf_devider->Multiplication(devider);
        if(*devidend >= *buf)
        good_div = true;
        else
        good_div = false;
    //
        if(good_div)
        {
            devidend->SubtractionS(buf);
            new_int->SummaryS(buf_devider);
        }
    //
        if(*devidend >= *buf) // true - можем разделить false - не можем
            good_devidend = true;
        else
            good_devidend = false;
        //
        if(!good_devidend)
            buf_devider->Update(divisionInTwo(buf_devider->Integer));
        //
        if(*devidend < *devider)
            end_div = true;
        else
            end_div = false;
    }
    integer->Sign = Second_Sign;
    Sign = First_Sign;
    req = new BigInt(devidend);
    free((void*)buf);
    free((void*)buf_devider);
    free((void*)devidend);
    free((void*)new_int);
    return req;
}
void BigInt::ModulationS(BigInt* integer)
{
    if(!integer)
        return;
    if(!integer->size)
    {
        if(size)
        {
            Sign = false;
            size = 0;
            free(Integer);
            Integer = NULL;
        }
        return;
    }
    if(!size)
        return;
    if(size < integer->size)
    {
        //std::cout<<size<<" a "<<integer->size<<" ";
        return;
    }
    bool new_Sign, end_div = false, good_div, good_devidend;
    BigInt *devidend, *devider, *new_int, *buf = new BigInt(0), *buf_devider, *req;
    if (Sign == integer->Sign)
        new_Sign = false;
    else
        new_Sign = true;
    bool First_Sign = Sign, Second_Sign = integer->Sign;
    Sign = false; integer->Sign = false;
    devidend = new BigInt(this);
    devider = integer;
    new_int = new BigInt(0);
    buf_devider = new BigInt(divisionInTwo(devidend->Integer));
    while(!end_div)
    {
        buf = buf_devider->Multiplication(devider);
        if(*devidend >= *buf)
            good_div = true;
        else
            good_div = false;
    //
        if(good_div)
        {
            devidend->SubtractionS(buf);
            new_int->SummaryS(buf_devider);
        }
    //
        if(*devidend >= *buf) // true - можем разделить false - не можем
            good_devidend = true;
        else
            good_devidend = false;
        //
        if(!good_devidend)
            buf_devider->Update(divisionInTwo(buf_devider->Integer));
            //
        if(*devidend >= *devider)
        end_div = false;
        else
            end_div = true;
    }
    integer->Sign = Second_Sign;
    Sign = First_Sign;
    req = new BigInt(devidend);
    free((void*)buf);
    free((void*)buf_devider);
    free((void*)devidend);
    Update(req->Integer);
    free((void*)req);
    free((void*)new_int);
}
void BigInt::Clear()
{
    free((void*)Integer);
    Sign = false;
    size = 0;
}
char* BigInt::Print()
{
    if(!size)
    {
        //std::cout<<0<<"\n";
        return "0";
    }
    char *str = new char[size + 2];
    size_t a = size;
    memcpy((void*)str, (void*)Integer, a);
    if(Sign)
    {
        str[0] = '-';
        memcpy((void*)(str+1), (void*)Integer, a);
        //std::cout<<"-";
        return str;
    }
    return str;
    //std::cout<<Integer<<"\n";
}
void BigInt::hello()
{
    std::cout<<"Hello World";
}
BigInt::~BigInt()
{
    free((void*)Integer);
    Sign = false;
    size = 0;
}
