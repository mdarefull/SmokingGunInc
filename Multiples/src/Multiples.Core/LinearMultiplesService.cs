using System;
using System.Collections.Generic;
using System.Linq;

namespace SmokingGunInc.Multiples
{
    /// <summary>
    /// Implementation of <see cref="IMultiplesService"/> that provides a linear implementation of <see cref="DetermineMultiple(ushort)"/>.
    /// </summary>
    public class LinearMultiplesService : IMultiplesService
    {
        /// <inheritdoc />
        public IReadOnlyCollection<Factor> Factors { get; private set; }

        /// <summary>
        /// Creates a new instance of <see cref="LinearMultiplesService"/>
        /// </summary>
        /// <param name="factors"></param>
        public LinearMultiplesService(params Factor[] factors)
        {
            if (factors.Length == 0)
            {
                throw new ArgumentException("Argument cannot be an empty collection.", nameof(factors));
            }

            Factors = factors;
        }

        /// <inheritdoc />
        public ulong DetermineMultiple(ushort position)
        {
            ValidatePositionParameter(position);

            var calculatedFactors = new List<ulong>(position) { 1 };
            InitializeFactors(calculatedFactors);

            while (calculatedFactors.Count < position)
            {
                CalculateNextFactor(calculatedFactors);
            }

            return calculatedFactors[position - 1];
        }
        private void InitializeFactors(IList<ulong> calculatedFactors)
        {
            Factors = Factors.Select(f => new Factor(f.Number)).ToArray();

            var minFactor = Factors.Min();
            calculatedFactors.Add(minFactor.Number);

            SetNextValue(minFactor, calculatedFactors);
        }

        private static void ValidatePositionParameter(ushort position)
        {
            if (position == 0)
            {
                throw new ArgumentException("Argument must not be 0", nameof(position));
            }
        }

        private void CalculateNextFactor(IList<ulong> calculatedFactors)
        {
            var minFactorValue = MinFactorValue();
            var nextValue = minFactorValue.NextValue;
            if (nextValue > calculatedFactors[^1])
            {
                calculatedFactors.Add(nextValue);
            }

            SetNextValue(minFactorValue, calculatedFactors);
        }
        private Factor MinFactorValue()
        {
            var minFactorValue = Factors.First();
            foreach (var factor in Factors.Skip(1))
            {
                if (minFactorValue.NextValue > factor.NextValue)
                {
                    minFactorValue = factor;
                }
            }

            return minFactorValue;
        }
        private static void SetNextValue(Factor factor, IList<ulong> calculatedFactors)
        {
            // If NextIndex is 0 then NextValue == Number, meaning the factor itself was just added to the list.
            //  Its NextValue always is Number^2.
            if (factor.NextIndex == 0)
            {
                factor.NextIndex = calculatedFactors.Count - 1;
            }
            else
            {
                factor.NextIndex++;
            }

            factor.NextValue = factor.Number * calculatedFactors[factor.NextIndex];
        }
    }
}
