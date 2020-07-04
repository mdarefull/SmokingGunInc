using System;
using System.Collections.Generic;
using System.Linq;

namespace SmokingGunInc.Multiples
{
    /// <summary>
    /// Implementation of <see cref="IMultiplesService"/> that provides a linear implementation of <see cref="DetermineMultiple(int, ulong[])"/>/>.
    /// </summary>
    public class LinearMultiplesService : IMultiplesService
    {
        /// <inheritdoc />
        public ulong DetermineMultiple(int position, params ulong[] numbers)
        {
            var (factors, multiples) = InitializeService(numbers, position);

            while (multiples.Count < position)
            {
                CalculateNextFactor(factors, multiples);
            }

            return multiples[position - 1];
        }
        private static (IReadOnlyCollection<Factor> factors, IList<ulong> multiples) InitializeService(ulong[] numbers, int position)
        {
            if (numbers.Length == 0)
            {
                throw new ArgumentException("Argument cannot be an empty collection", nameof(numbers));
            }

            if (numbers.Any(n => n <= 1))
            {
                throw new ArgumentException("Every provided number argument must be greater than \"1\"", nameof(numbers));
            }

            if (position <= 0)
            {
                throw new ArgumentException("Argument must be greater than 0", nameof(position));
            }

            var factors = numbers.Select(n => new Factor(n)).ToArray();
            var multiples = new List<ulong>(position) { 1 };

            var minFactor = MinByNumber(factors);
            multiples.Add(minFactor.Number);

            SetNextValue(minFactor, multiples);

            return (factors, multiples);
        }

        private static void CalculateNextFactor(IReadOnlyCollection<Factor> factors, IList<ulong> multiples)
        {
            var minFactorValue = MinByValue(factors);
            var nextValue = minFactorValue.NextValue;
            if (nextValue > multiples[^1])
            {
                multiples.Add(nextValue);
            }

            SetNextValue(minFactorValue, multiples);
        }
        private static Factor MinByNumber(IReadOnlyCollection<Factor> factors)
        {
            var minFactor = factors.First();
            foreach (var factor in factors.Skip(1))
            {
                if (minFactor.Number > factor.Number)
                {
                    minFactor = factor;
                }
            }

            return minFactor;
        }
        private static Factor MinByValue(IReadOnlyCollection<Factor> factors)
        {
            var minValue = factors.First();
            foreach (var factor in factors.Skip(1))
            {
                if (minValue.NextValue > factor.NextValue)
                {
                    minValue = factor;
                }
            }

            return minValue;
        }
        private static void SetNextValue(Factor factor, IList<ulong> multiples)
        {
            factor.NextIndex++;
            factor.NextValue = factor.Number * multiples[factor.NextIndex];
        }
    }
}
