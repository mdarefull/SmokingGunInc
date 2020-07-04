namespace SmokingGunInc.Multiples
{
    /// <summary>
    /// Service to determine the multiple of factors following different criteria.
    /// </summary>
    public interface IMultiplesService
    {
        /// <summary>
        /// Determines the number on the given <paramref name="position"/> in the sorted list of numbers in the form <code>n = F1^f1 * F2^f2 * ... * Fn^fn</code>
        /// where <code>Fi</code> is an element of <paramref name="numbers"/> and <code>fi</code> is an integer greater or equal to 0.
        /// </summary>
        /// <param name="position">The position in the list of the number to be calculated. <paramref name="position"/> must be between 1 and 13282 inclusive.</param>
        /// <param name="numbers">Collection of factors to use for the computation</param>
        /// <returns>The value of the number in the list that takes the position <paramref name="position"/>.</returns>
        ulong DetermineMultiple(int position, params ulong[] numbers);
    }
}
