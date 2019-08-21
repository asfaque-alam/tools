using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace ProcessMonitor
{
    class Program
    {
        const Int32 DEFAULT_RUN_DURATION_SECS = 10; //10 secs
       

        
        static void Main(string[] args)
        {
            try
            {
                foreach (string s in args)
                {
                    if (s == "-log")
                    {
                        Logger.LogToFile(true);
                        break;
                    }
                }
                

                cmdline cmdline = new cmdline();
                //cmdline.PID = 1680;
                cmdline.RunDurationInSecs = DEFAULT_RUN_DURATION_SECS;

                if (!cmdline.parseCmdline(args))
                {
                    //Console.WriteLine("Invalid cmdline or incomplete commandline");
                    return;
                }
                //Logger.Log

                ///////Logging on console
                Logger.Log("Process ID to monitor: " + cmdline.PID);
                if (cmdline.CheckMemoryUsageTHreshold)
                {
                    Logger.Log("Virtual memory size of process to start WPR: " + cmdline.Threshold/(1024*1024) + "MB");
                }
                else if (cmdline.CheckCpuUsagesThreshold)
                {
                    Logger.Log("CPU usage of PID" + cmdline.PID + " to start WPR: " + cmdline.Threshold + "%");
                }

                Logger.Log("WPR running duration: " + cmdline.RunDurationInSecs + "Secs");
                ///////Logging on console ends


                LogCollector logcollector = new LogCollector(cmdline);
                logcollector.start();
            }
            catch (Exception e)
            {
                Logger.Log("Exception in main: " + e.StackTrace);
            }

            
        }
    }
}
