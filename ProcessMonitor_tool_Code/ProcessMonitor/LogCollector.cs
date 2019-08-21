using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ProcessMonitor
{
    class LogCollector
    {
        private cmdline _cmdline;
        
        public LogCollector(cmdline cmdline)
        {
            _cmdline = cmdline;

            //Thread newThread = new Thread(this.DoWork);
        }

        public bool start()
        {

            if (_cmdline.RunXperf == true && _cmdline.CheckCpuUsagesThreshold)
            {
                MonitorAndStartLog(new cpuUsagesMonitor(), new xperfTracer());
            }
            else if (_cmdline.RunXperf == true && _cmdline.CheckMemoryUsageTHreshold)
            {
                MonitorAndStartLog(new VirtualMemoryMonitor(), new xperfTracer());
            }
            else if (_cmdline.GenerateBSOD == true && _cmdline.CheckMemoryUsageTHreshold)
            {
                MonitorAndStartLog(new VirtualMemoryMonitor(), new BSODGenerator());
            }
            else if (_cmdline.GenerateBSOD && _cmdline.CheckCpuUsagesThreshold)
            {
                MonitorAndStartLog(new cpuUsagesMonitor(), new BSODGenerator());
            }

            return true;
        }

        public bool MonitorAndStartLog(IMonitor monitor, ILogType logtype)
        {
            bool running = false;
            Int64 logstartTickCount = 0;

            Int32 monitorInterval = monitor.getMonitorInterval()*1000;//In Ms

            try
            {
                while (true)
                {
                    
                    Int64 threshold = monitor.monitor(_cmdline.PID);
                    
                    if (running)
                    {
                        Int64 currentTickcount = System.Environment.TickCount;

                        if (currentTickcount >= logstartTickCount + (Int64)_cmdline.RunDurationInSecs*1000)
                        {
                            logtype.stop();
                            running = false;
                            break;
                        }
                    }
                    else
                    {
                        if (threshold >= _cmdline.Threshold)
                        {
                            if (logtype.start())
                            {
                                Logger.Log("Running log collection for " + _cmdline.RunDurationInSecs + "Secs!!!");
                                logstartTickCount = System.Environment.TickCount;
                                running = true;
                            }
                            else
                            {
                                Logger.Log("Failed to run log collection. Exit");
                                break;
                            }
                        }
                    }
                    Thread.Sleep(monitorInterval);
                }
            }

            catch (Exception e)
            {
                Logger.Log("Exception in MonitorAndStartLog: " + e.Message);
            }
            finally
            {
              
                logtype.stop();
                running = false;
              
            }
            return true;
        }
    }
}
