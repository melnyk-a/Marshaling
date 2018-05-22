using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace Marshaling
{
    class Program
    {
        internal static class NativeMethods
        {
            private const string DllPath = @"..\..\..\Debug\Functions.dll";


            [DllImport(DllPath, EntryPoint = "GetLiteral")]
            public static extern string GetLiteral1();


            [DllImport(DllPath, EntryPoint = "GetLiteral")]
            private static extern IntPtr _GetLiteral();


            public static string GetLiteral2() => Marshal.PtrToStringAnsi(_GetLiteral());


            [DllImport(DllPath, CharSet = CharSet.Ansi)]
            [return: MarshalAs(UnmanagedType.LPWStr)]
            public static extern string GetComputerFolderName1();


            [DllImport(DllPath, CharSet = CharSet.Ansi, EntryPoint = "GetComputerFolderName2")]
            private static extern IntPtr _GetComputerFolderName2();

            public static string GetComputerFolderName2() => Marshal.PtrToStringAnsi(_GetComputerFolderName2());


            [DllImport(DllPath, CharSet = CharSet.Ansi)]
            public static extern string GetComputerFolderName3();

            [DllImport(DllPath)]
            public static extern void GetString(StringBuilder buffer, int bufferSize);


            
        }
        static void Main(string[] args)
        {
            //string str1 = NativeMethods.GetLiteral1();
            //Console.WriteLine(str1);          // ошибка на этапе выполнения

            //string str2 = NativeMethods.GetLiteral2();
            //Console.WriteLine(str2);            // вывелся только один символ

            // string str3 = NativeMethods.GetComputerFolderName1();
            // Console.WriteLine(str3);        // ошибка на этапе выполнения

            //string str4 = NativeMethods.GetComputerFolderName2();
            //Console.WriteLine(str4);        //все ок

            string str5 = NativeMethods.GetComputerFolderName3();
            Console.WriteLine(str5);        //непонятная кодировка

            StringBuilder builder = new StringBuilder(20);
            NativeMethods.GetString(builder,20);
            Console.WriteLine(builder);        //ошибка на этапе выполнения
        }
    }
}
