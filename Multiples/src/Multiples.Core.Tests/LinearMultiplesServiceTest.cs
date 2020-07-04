using FluentAssertions;

using System;

using Xunit;

namespace SmokingGunInc.Multiples
{
    public class LinearMultiplesServiceTest
    {
        [Theory]
        [InlineData(1, 1, 2ul, 3ul, 5ul)]
        [InlineData(2, 2, 2ul, 3ul, 5ul)]
        [InlineData(3, 3, 2ul, 3ul, 5ul)]
        [InlineData(4, 4, 2ul, 3ul, 5ul)]
        [InlineData(5, 5, 2ul, 3ul, 5ul)]
        [InlineData(6, 6, 2ul, 3ul, 5ul)]
        [InlineData(7, 8, 2ul, 3ul, 5ul)]
        [InlineData(8, 9, 2ul, 3ul, 5ul)]
        [InlineData(9, 10, 2ul, 3ul, 5ul)]
        [InlineData(10, 12, 2ul, 3ul, 5ul)]
        [InlineData(11, 15, 2ul, 3ul, 5ul)]
        [InlineData(12, 16, 2ul, 3ul, 5ul)]
        [InlineData(13, 18, 2ul, 3ul, 5ul)]
        [InlineData(14, 20, 2ul, 3ul, 5ul)]
        [InlineData(15, 24, 2ul, 3ul, 5ul)]
        [InlineData(16, 25, 2ul, 3ul, 5ul)]
        [InlineData(17, 27, 2ul, 3ul, 5ul)]
        [InlineData(18, 30, 2ul, 3ul, 5ul)]
        [InlineData(1500, 859963392, 2ul, 3ul, 5ul)]
        [InlineData(100, 1536, 2ul, 3ul, 5ul)]
        [InlineData(100, 6860, 2ul, 5ul, 7ul)]
        [InlineData(100, 1536, 2ul, 3ul, 5ul, 5ul)]
        [InlineData(100, 33075, 3ul, 5ul, 7ul)]
        [InlineData(20, 192, 4ul, 8ul, 3ul)]
        public void DetermineMultiple_ReturnsExpected(ushort position, ulong expectedResult, params ulong[] numbers)
        {
            // Arrange
            var subject = new LinearMultiplesService();

            // Act
            var result = subject.DetermineMultiple(position, numbers);

            // Assert
            result.Should().Be(expectedResult);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(-1)]
        [InlineData(-100)]
        public void DetermineMultiple_InvalidPosition_ArgumentException(int position)
        {
            // Arrange
            var subject = new LinearMultiplesService();

            // Act & Assert
            subject
                .Invoking(s => s.DetermineMultiple(position, 2))
                .Should()
                .ThrowExactly<ArgumentException>()
                .WithMessage("Argument must be greater than 0 (Parameter 'position')");
        }

        [Fact]
        public void DetermineMultiple_EmptyNumbersList_ArgumentException()
        {
            // Arrange
            var subject = new LinearMultiplesService();

            // Act & Assert
            subject
                .Invoking(s => s.DetermineMultiple(2))
                .Should()
                .ThrowExactly<ArgumentException>()
                .WithMessage("Argument cannot be an empty collection (Parameter 'numbers')");
        }

        [Theory]
        [InlineData(0ul)]
        [InlineData(1ul)]
        [InlineData(2ul, 3ul, 0ul)]
        [InlineData(2ul, 5ul, 1ul)]
        public void DetermineMultiple_InvalidNumbers_ArgumentException(params ulong[] numbers)
        {
            // Arrange
            var subject = new LinearMultiplesService();

            // Act & Assert
            subject
                .Invoking(s => s.DetermineMultiple(2, numbers))
                .Should()
                .ThrowExactly<ArgumentException>()
                .WithMessage("Every provided number argument must be greater than \"1\" (Parameter 'numbers')");
        }
    }
}
