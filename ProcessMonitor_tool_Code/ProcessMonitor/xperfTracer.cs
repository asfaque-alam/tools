using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace ProcessMonitor
{
    class xperfTracer:ILogType
    {
       // bool bTraceStarted = false;
        //String xperf_start_batch_file = "\\start_WPR_tracing.bat";
        //String xperf_stop_batch_file = "\\stop_WPR_tracing.bat";
        public  bool start()
        {
            try
            {
                String xperfPath = System.IO.Directory.GetCurrentDirectory();
                xperfPath = xperfPath + "\\start_WPR_tracing.bat";

                ProcessStartInfo processInfo = new ProcessStartInfo(xperfPath);
                processInfo.CreateNoWindow = false;
                processInfo.UseShellExecute = true;

                Process process;
                process = Process.Start(processInfo);

                Logger.Log("Starting Xperf trace collection");
            }
            catch (Exception e)
            {
                Logger.Log("Exception in xperfTracer::start" + e.Message);
                return false;
            }
            
            return true;
        }

        public bool stop()
        {
            try
            {
                String xperfPath = System.IO.Directory.GetCurrentDirectory();
                xperfPath = xperfPath + "\\stop_WPR_tracing.bat";

                ProcessStartInfo processInfo = new ProcessStartInfo(xperfPath);
                processInfo.CreateNoWindow = false;
                processInfo.UseShellExecute = true;

                Process process;
                process = Process.Start(processInfo);

                Logger.Log("!!!Stop xperf trace collection!!!");
            }
            catch (Exception e)
            {
                Logger.Log("Exception in xperfTracer::Stop() " + e.Message);
            }

            return true;

        }
    }
}
