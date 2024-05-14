#include <iostream>

using namespace std;

class Counter
{
    int *bit, num;
    public:
        Counter(int size);
        ~Counter();
        void counting();
};

void Counter :: counting()
            {
                int i = 0;
                while(i < num && bit[i] == 1)
                {
                    bit[i++] = 0;
                }
                if(i < num)
                    bit[i] = 1;
                for(int i = num-1; i >= 0; i--)
                {
                    cout << bit[i];
                }
                cout << endl;
            }
Counter :: Counter(int size)
            {
                num = size;
                bit = new int[num];
                for(int i = 0; i < num; i++)
                {
                    bit[i] = 0;
                }
            }
Counter :: ~Counter()
            {
                delete[] bit;
            }
int main()
{
    int lim;
    cout << "Enter the number of Bits in the counter: ";
    cin >> lim;
    Counter C(lim);
    int num = 1;
    num <<= lim;
    for(int i = 0; i < num; i++)
    {
        C.counting();
    }
    return 0;
}