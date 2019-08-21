using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.Management;

namespace ProcessMonitor
{
    class WMIProcess_Query
    {


        public Hashtable processProperties(Int32 processID)
        {
            ArrayList processPropertiesArray = new ArrayList();
            Hashtable ht = new Hashtable();


            SelectQuery msQuery = new SelectQuery("SELECT * FROM Win32_Process Where ProcessId = '" + processID + "'");
            
            ManagementObjectSearcher searcher =  new ManagementObjectSearcher(msQuery);

            foreach(ManagementObject item in searcher.Get())
            {

              /* try{ processPropertiesArray.Add("CommandLine: " + item["CommandLine"].ToString()); }
               catch (SystemException){}                    */
               // try{ processPropertiesArray.Add("CreationDate: " + item["CreationDate"].ToString()); }
               // catch (SystemException){}
                /*try{ processPropertiesArray.Add("ExecutablePath: " + item["ExecutablePath"].ToString()); }
                catch (SystemException){}*/
                //try{ processPropertiesArray.Add("ExecutionState: " + item["ExecutionState"].ToString()); }
                //catch (SystemException){}
                /*try{ processPropertiesArray.Add("Handle: " + item["Handle"].ToString()); }
                catch (SystemException){}
                try{ processPropertiesArray.Add("HandleCount: " + item["HandleCount"].ToString()); }
                catch (SystemException){}
                try{ processPropertiesArray.Add("InstallDate: " + item["InstallDate"].ToString()); }
                catch (SystemException){}*/
                try{ processPropertiesArray.Add("KernelModeTime: " + item["KernelModeTime"].ToString()); }
                catch (SystemException){}
                try{ processPropertiesArray.Add("MaximumWorkingSetSize: " + item["MaximumWorkingSetSize"].ToString()); }
                catch (SystemException){}
               /* try{ processPropertiesArray.Add("Memory Usage: " + ProcessMethod.TranslateMemoryUsage(item["WorkingSetSize"].ToString())); }
                catch (SystemException){}*/
              /*  try{ processPropertiesArray.Add("MinimumWorkingSetSize: " + item["MinimumWorkingSetSize"].ToString()); }
                catch (SystemException){}*/
                try{ processPropertiesArray.Add("Name: " + item["Name"].ToString()); }
                catch (SystemException){}    
                /*try{ processPropertiesArray.Add("OSName: " + item["OSName"].ToString()); }
                catch (SystemException){}
                try{ processPropertiesArray.Add("PageFaults: " + item["PageFaults"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("PageFileUsage: " + item["PageFileUsage"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("ParentProcessId: " + item["ParentProcessId"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("PeakPageFileUsage: " + item["PeakPageFileUsage"].ToString()); }
                catch (SystemException){} */
                try { processPropertiesArray.Add("PeakVirtualSize: " + TranslateVirtualSize(item["PeakVirtualSize"].ToString())); }
                catch (SystemException){}    
                /*try{ processPropertiesArray.Add("PeakWorkingSetSize: " + item["PeakWorkingSetSize"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("Priority: " + item["Priority"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("PrivatePageCount: " + item["PrivatePageCount"].ToString()); }
                catch (SystemException){}    */
                try{ processPropertiesArray.Add("ProcessId: " + item["ProcessId"].ToString()); }
                catch (SystemException){}    
                /*try{ processPropertiesArray.Add("QuotaNonPagedPoolUsage: " + item["QuotaNonPagedPoolUsage"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("QuotaPagedPoolUsage: " + item["QuotaPagedPoolUsage"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("QuotaPeakNonPagedPoolUsage: " + item["QuotaPeakNonPagedPoolUsage"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("QuotaPeakPagedPoolUsage: " + item["QuotaPeakPagedPoolUsage"].ToString()); }
                catch (SystemException){}    */
                try{ processPropertiesArray.Add("SessionId: " + item["SessionId"].ToString()); }
                catch (SystemException){}    
                /*try{ processPropertiesArray.Add("Status: " + item["Status"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("TerminationDate: " + item["TerminationDate"].ToString()); }
                catch (SystemException){}    
                try{ processPropertiesArray.Add("ThreadCount: " + item["ThreadCount"].ToString()); }
                catch (SystemException){}    */
                try{ processPropertiesArray.Add("UserModeTime: " + item["UserModeTime"].ToString()); }
                catch (SystemException){}
                try{ processPropertiesArray.Add("VirtualSize: " + WMIProcess_Query.TranslateVirtualSize(item["VirtualSize"].ToString())); }
                catch (SystemException){}    
                //try{ processPropertiesArray.Add("WindowsVersion: " + item["WindowsVersion"].ToString()); }
                //catch (SystemException){}    
                try { processPropertiesArray.Add("WorkingSetSize: " + WMIProcess_Query.TranslateVirtualSize(item["WorkingSetSize"].ToString())); }
                catch (SystemException){}

                ht.Add("VirtualSize", item["VirtualSize"].ToString());
                ht.Add("WorkingSetSize", item["WorkingSetSize"].ToString());
            }

            Logger.Log("----------------------------");
            foreach (string item in processPropertiesArray)
            {
                Logger.Log(item.ToString());
            }

            return ht;

        }
        public Int32 cpuUsageOfProcess(Int32 PID)
        {
            Int32 cpuUsages = 0;
            try
            {
                ManagementObjectSearcher searcher =
                    new ManagementObjectSearcher("root\\CIMV2",
                    "SELECT * FROM Win32_PerfFormattedData_PerfProc_Process");

                foreach (ManagementObject queryObj in searcher.Get())
                {
                    if (queryObj["IDProcess"].ToString() == PID.ToString())
                    {
                        Logger.Log("----------------------------------");
                        Logger.Log("Name: "+ queryObj["Name"].ToString());
                        Logger.Log("ProcessID: " + queryObj["IDProcess"].ToString());
                        Logger.Log("PercentProcessorTime:" + queryObj["PercentProcessorTime"].ToString());

                        cpuUsages = Convert.ToInt32(queryObj["PercentProcessorTime"]);
                        
                        break;

                    }
                    
                }
            }
            catch (ManagementException e)
            {
                Console.WriteLine("An error occurred while querying for WMI data for processor time: " + e.Message);
            }
            return cpuUsages;

        }

        public static String TranslateVirtualSize(String sVirtualsize)
        {
            int iVirtualSize = Convert.ToInt32(sVirtualsize);
            iVirtualSize = iVirtualSize /(1024*1024);
            return (iVirtualSize.ToString() + " MB");
           
        }
    }
}
