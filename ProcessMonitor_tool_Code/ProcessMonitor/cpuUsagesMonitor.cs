using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessMonitor
{
    class cpuUsagesMonitor: IMonitor
    {
        private Int32 MONITOR_INTERVAL = 2; //2 secs

        public cpuUsagesMonitor(Int32 monitorInterval)
        {
            MONITOR_INTERVAL = monitorInterval;
        }

        public cpuUsagesMonitor()
        {
         
        }
        public Int64 monitor(Int32 PID)
        {
            Int64 cpuUsages = 0;
            try
            {
                WMIProcess_Query pr = new WMIProcess_Query();
                cpuUsages = (Int64)pr.cpuUsageOfProcess(PID);
            }
            catch (Exception e)
            {
                Logger.Log("cpuUsagesMonitor.monitor:" + e.Message);
            }
            return cpuUsages;
        }
        public Int32 getMonitorInterval()
        {
            return MONITOR_INTERVAL;

        }
    }
}
