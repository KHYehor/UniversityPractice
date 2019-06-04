using System;

namespace Hmeluk
{
    class Program
    {
        static void Main()
        {
            int number, indexof4, indexof3, indexof2, indexof1;
            string input, num, output, d4, d3, d2, d1;
            bool error;
            string[] digit1 = { "I", "II", "III", "IV", "V", "VI", "VII", "IIX", "IX", "N" };
            string[] digit2 = { "X", "XX", "XXX", "XL", "L", "LX", "LXX", "XXC", "XC", "N" };
            string[] digit3 = { "C", "CC", "CCC", "CD", "D", "DC", "DCC", "CCM", "CM", "N" };
            string[] digit4 = { "M", "MM", "MMM" };
            string[] digit = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0" };
            Console.WriteLine("Добро Пожаловать в трансформатор чисел!");
            Console.WriteLine("Введите число в интервале[0; 3000].");
            do
            {
                Console.WriteLine("Введите exit для выхода.");
                input = Console.ReadLine();
                if (input == "exit") break;
                error = int.TryParse(input, out number);
                if (!error || number > 3000)
                {
                    Console.WriteLine("Введите, пожалуйста, число в промежутке [0; 3000]!");
                }

                else
                {
                    num = number.ToString();
                    switch (num.Length)
                    {
                        case 1:
                            d1 = Char.ToString(num[0]);
                            indexof1 = Array.IndexOf(digit, d1);
                            output = digit1[indexof1];
                            Console.WriteLine(output);
                            break;
                        case 2:
                            d1 = Char.ToString(num[0]);
                            d2 = Char.ToString(num[1]);
                            indexof1 = Array.IndexOf(digit, d1);
                            indexof2 = Array.IndexOf(digit, d2);
                            output = digit2[indexof1] + digit1[indexof2];
                            Console.WriteLine(output);
                            break;
                        case 3:
                            d1 = Char.ToString(num[0]);
                            d2 = Char.ToString(num[1]);
                            d3 = Char.ToString(num[2]);
                            indexof1 = Array.IndexOf(digit, d1);
                            indexof2 = Array.IndexOf(digit, d2);
                            indexof3 = Array.IndexOf(digit, d3);
                            output = digit3[indexof1] + digit2[indexof2] + digit1[indexof3];
                            Console.WriteLine(output);
                            break;
                        case 4:
                            d1 = Char.ToString(num[0]);
                            d2 = Char.ToString(num[1]);
                            d3 = Char.ToString(num[2]);
                            d4 = Char.ToString(num[3]);
                            indexof1 = Array.IndexOf(digit, d1);
                            indexof2 = Array.IndexOf(digit, d2);
                            indexof3 = Array.IndexOf(digit, d3);
                            indexof4 = Array.IndexOf(digit, d4);
                            output = digit4[indexof1] + digit3[indexof2] + digit2[indexof3] + digit1[indexof4];
                            Console.WriteLine(output);
                            break;
                        default:
                            break;
                    }
                }
            } while (true);
        }
    }
}