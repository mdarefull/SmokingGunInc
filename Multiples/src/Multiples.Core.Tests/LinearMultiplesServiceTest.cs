using FluentAssertions;

using System;
using System.Linq;

using Xunit;

namespace SmokingGunInc.Multiples
{
    public class LinearMultiplesServiceTest
    {
        [Fact]
        public void Constructor_InstantiatesService()
        {
            // Arrange
            var factors = new[] { new Factor(3), new Factor(5), new Factor(2) };

            // Act
            var subject = new LinearMultiplesService(factors);

            // Assert
            subject.Factors.Should().BeEquivalentTo(factors);
        }

        [Fact]
        public void Constructor_NoFactors_ArgumentException()
        {
            // Arrange
            LinearMultiplesService instantiation() => new LinearMultiplesService();

            // Assert
            Assert.Throws<ArgumentException>("factors", instantiation);
        }

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
            var factors = numbers.Select(n => new Factor(n)).ToArray();
            var subject = new LinearMultiplesService(factors);

            // Act
            var result = subject.DetermineMultiple(position);

            // Assert
            result.Should().Be(expectedResult);
        }

        [Fact]
        public void DetermineMultiple_PositionEquals0_ArgumentException()
        {
            // Arrange
            var subject = new LinearMultiplesService(2, 3, 5);

            void invocation() => subject.DetermineMultiple(0);

            // Assert
            Assert.Throws<ArgumentException>("position", invocation);
        }
    }
}
