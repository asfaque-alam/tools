using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessMonitor
{
    class cmdline
    {
        private Int32 _pid = 0;
        private Int32 _runDurationInSecs = 0;
        private Int32 _threshold = 0;

        private bool _runXperf = false;
        private bool _generateBSOD = false;
        private bool _checkMemorythreshold = false;
        private bool _checkCpuThreshold = false;

        /*public bool parseCmdLineEx(string[] args)
        {
            string xperf = "xperf";
            string bsod = "bsod";
            string switchMemoryThreshold = "-m";
            string switchcpuThreshold = "-c";

            foreach (string s in args)
            {

                if (xperf == s)
                {
                    this.RunXperf = true;

                }
                else if (bsod == s)
                {
                    this.GenerateBSOD = true;
                }
                else if (switchMemoryThreshold == s)
                {
                    this._checkMemorythreshold = true;

                }
                else if (switchcpuThreshold == s)
                {
                    this._checkCpuThreshold = true;
                }
            }
            return true;
        }*/


        public bool parseCmdline(string[] args)
        {
            string xperf = "-xperf";
            string bsod = "-bsod";
            string switchMemoryThreshold = "-m";
            string switchcpuThreshold = "-c";

            if (args.Length < 4)
            {
                Logger.Log("Incomplete commandLine arguments.Failed to run tool!!!");
                return false;
            }

            if (args.Length >= 3)
            {
                //Logtype to collect
                if (xperf == args[0].ToString())
                {
                    this.RunXperf = true;

                }
                else if (bsod == args[0].ToString())
                {
                    this.GenerateBSOD = true;
                }

                //What to monitor CPU or process address sapce.
                if (switchMemoryThreshold == args[1].ToString())
                {
                    this._checkMemorythreshold = true;

                }
                else if (switchcpuThreshold == args[1].ToString())
                {
                    this._checkCpuThreshold = true;
                }

                //Process ID
                this._pid = Convert.ToInt32(args[2].ToString());
            }
            if (args.Length >= 4)
            {
                this._threshold = Convert.ToInt32(args[3].ToString());
                if (this.CheckMemoryUsageTHreshold)
                {
                    this._threshold = this._threshold * 1024 * 1024; //Convert to Bytes
                }
            }
            if (args.Length >= 5)
            {
                this._runDurationInSecs = Convert.ToInt32(args[4].ToString());
            }

            return true;
        }

        //Setter, getter.
        public Int32 PID
        {
            get { return _pid; }
            set { _pid = value; }
        }

        
        public Int32 RunDurationInSecs
        {
            get { return _runDurationInSecs; }
            set { _runDurationInSecs = value; }
        }
        public bool RunXperf
        {
            get { return _runXperf; }
            set { _runXperf = value; }
        }
        public bool GenerateBSOD
        {
            get { return _generateBSOD; }
            set { _generateBSOD = value; }
        }
        public bool CheckMemoryUsageTHreshold
        {
            get { return _checkMemorythreshold; }
            set { _checkMemorythreshold = value; }
        }
        public bool CheckCpuUsagesThreshold
        {
            get { return _checkCpuThreshold; }
            set { _checkCpuThreshold = value; }
        }
        public Int32 Threshold
        {
            get { return _threshold; }
            set { _threshold = value; }
        }
    }
}
