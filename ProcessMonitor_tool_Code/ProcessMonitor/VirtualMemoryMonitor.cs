using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessMonitor
{
    class VirtualMemoryMonitor:IMonitor
    {
        private Int32 MONITOR_INTERVAL = 5; //5 secs

        public VirtualMemoryMonitor(Int32 monitorInterval)
        {
            MONITOR_INTERVAL = monitorInterval;
        }
        public VirtualMemoryMonitor()
        {
            
        }

        public Int64 monitor(Int32 PID)
        {
            Int64 virtualSize = 0;
            try
            {
                WMIProcess_Query wmi_query = new WMIProcess_Query();
                System.Collections.Hashtable ht = wmi_query.processProperties(PID);

                virtualSize = Convert.ToInt64(ht["VirtualSize"].ToString());
            }
            catch (Exception e)
            {
                Logger.Log("Exception VirtualMemoryMonitor: " + e.Message);
            }

            //Int64 workingSize = Convert.ToInt64(ht["WorkingSetSize"].ToString());

            return virtualSize;
           

        }

        public Int32 getMonitorInterval()
        {
            return MONITOR_INTERVAL;

        }
    }
}
