using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessMonitor
{
    interface ILogType
    {
         bool start();
         bool stop();
    }
}
