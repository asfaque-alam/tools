using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace ProcessMonitor
{
    class BSODGenerator:ILogType
    {
        public bool start()
        {
            try
            {
                String notMyFaultPath = System.IO.Directory.GetCurrentDirectory();
                notMyFaultPath = notMyFaultPath + "\\NotMyFault.exe";

                ProcessStartInfo processInfo = new ProcessStartInfo(notMyFaultPath);
                processInfo.CreateNoWindow = false;
                processInfo.UseShellExecute = true;
                processInfo.Arguments = "/crash";

                Logger.Log("Generate BSOD!!!!");
                Process process;
                process = Process.Start(processInfo);
            }
            catch (Exception e)
            {
                Logger.Log("Exception in BSODGenerator::start() " + e.Message);
                return false;
            }
            return true;
        }

        public bool stop()
        {
            return true;
        }
    }
}
