using System;

namespace SmokingGunInc.Multiples
{
    /// <summary>
    /// Class that represents a factor to be used by <see cref="IMultiplesService"/>.
    /// </summary>
    public class Factor : IComparable<Factor>
    {
        /// <summary>
        /// Specifies one of the factors to be considered for <see cref="IMultiplesService"/> calculations.
        /// </summary>
        public ulong Number { get; }
        internal int NextIndex { get; set; }
        internal ulong NextValue { get; set; }

        /// <summary>
        /// Creates a new instance of a <see cref="Number"/>.
        /// </summary>
        /// <param name="factor">
        /// The value <see cref="Number"/> for this <see cref="Factor"/>. Must be greater than 1
        /// </param>
        /// <exception cref="ArgumentException">If <paramref name="factor"/> is smaller or equal than 1.</exception>
        public Factor(ulong factor)
        {
            if (factor <= 1)
            {
                throw new ArgumentException($"Argument: \"{factor}\" must be greater than \"1\"", nameof(factor));
            }

            Number = factor;
            NextValue = factor;
        }

        /// <summary>
        /// Implicit operator to create a <see cref="Factor"/> from an <see cref="ulong"/>.
        /// </summary>
        /// <param name="factor"></param>
        public static implicit operator Factor(ulong factor) => new Factor(factor);

        /// <summary>
        /// Converts an <see cref="ulong"/> into a <see cref="Factor"/>.
        /// </summary>
        /// <param name="factor">The value to be converted to a <see cref="Factor"/>.</param>
        /// <returns>A <see cref="Factor"/> with <see cref="Number"/> equals to <paramref name="factor"/>.</returns>
        public static Factor ToFactor(ulong factor) => factor;

        /// <summary>
        /// Compares this <see cref="Factor"/> to <paramref name="other"/> using their <see cref="Number"/> properties as reference.
        /// </summary>
        /// <param name="other">The other <see cref="Factor"/> to compare this <see cref="Factor"/> to.</param>
        /// <returns>
        /// <code>0</code> if both <see cref="Factor"/> are the same.
        /// A number greater than 0 if this <see cref="Factor"/> is greater than <paramref name="other"/>.
        /// A number smaller than 0 if this <see cref="Factor"/> is smaller than <paramref name="other"/>.
        /// </returns>
        public int CompareTo(Factor other) => Number.CompareTo(other?.Number);
    }
}
