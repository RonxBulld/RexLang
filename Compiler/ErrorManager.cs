using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Compiler
{
    class ErrorManager
    {
        enum ErrorSerious
        {
            Notify,
            Warning,
            Error,
            Fatal
        };
        private void Display(ErrorSerious serious, string fmt, params object[] args)
        {
            string msg = String.Format(fmt, args);
            Console.WriteLine("[{0}]{1} {2}", DateTime.Now, serious.ToString(), msg);
        }
        public bool VersionFailed(int req_ver, int act_ver)
        {
            this.Display(ErrorSerious.Fatal, "编译器只能识别版本号为{0}的程序，而当前程序版本号为{1}。", req_ver, act_ver);
            return false;
        }

        public bool DimensionMustMoreThanZero(int dimension)
        {
            this.Display(ErrorSerious.Error, "数组维度的定义必须是一个不小于0的正整数，{0}是不允许的。", dimension);
            return false;
        }

        public bool OperatorIsInvalid(string type_text)
        {
            this.Display(ErrorSerious.Error, "无效的运算符-{0}。", type_text);
            return false;
        }
    }
}
