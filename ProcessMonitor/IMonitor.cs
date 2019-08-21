using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessMonitor
{
    interface IMonitor
    {
        Int64  monitor(Int32 PID);
        Int32 getMonitorInterval();
    }
}
