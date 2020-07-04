namespace SmokingGunInc.Multiples
{
    internal class Factor
    {
        public ulong Number { get; }
        public int NextIndex { get; set; }
        public ulong NextValue { get; set; }

        public Factor(ulong number)
        {
            Number = number;
            NextValue = number;
            NextIndex = 0;
        }
    }
}
