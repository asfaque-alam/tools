using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace ProcessMonitor
{
    class Logger
    {
        public static bool _logToFile = false;
        public static String _logPath = Directory.GetCurrentDirectory() + "\\SymcProcessMonitor.log";
        public static void Log(String logstring)
        {
            try
            {
                //logstring = logstring;
                System.Console.WriteLine(logstring);

                if (_logToFile)
                {
                    logstring = "\n" + DateTime.UtcNow.ToLocalTime().ToString() + " " + logstring;
                    File.AppendAllText(_logPath, logstring);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception in logging: " + e.Message);
            }
        }

        public static void LogToFile(bool logtofile)
        {
            _logToFile = logtofile;
        }
    }
}
