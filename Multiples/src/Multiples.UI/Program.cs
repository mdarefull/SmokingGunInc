
using System;

namespace SmokingGunInc.Multiples
{
    public static class Program
    {
        private static void Main()
        {
            var service = InstantiateService();

            Console.WriteLine("Welcome to 2, 3 and 5 Multiples Calculator Program...");
            while (true)
            {
                try
                {
                    Console.WriteLine("---------------------------------------------------------");
                    Console.WriteLine();
                    Console.Write("Enter the position of the multiple to calculate: ");
                    var line = Console.ReadLine();

                    if (!ushort.TryParse(line, out var position) || position > 13282)
                    {
                        Console.WriteLine("Invalid position! Try again!");
                        continue;
                    }

                    var result = service.DetermineMultiple(position, 2, 3, 5);
                    Console.WriteLine($"The multiple in position \"{position}\" is \"{result}\"");
                }
                catch (Exception)
                {
                    Console.WriteLine("Oops! An unexpected error occurred :(. Please be nicer next time ;)");
                }
            }
        }

        private static IMultiplesService InstantiateService() => new LinearMultiplesService();
    }
}
