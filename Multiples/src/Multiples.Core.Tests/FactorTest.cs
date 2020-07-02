using FluentAssertions;

using System;
using System.Collections.Generic;

using Xunit;

namespace SmokingGunInc.Multiples
{
    public class FactorTest
    {
        #region Constructor
        [Fact]
        public void Constructor_InstantiatesNewFactor()
        {
            // Arrange
            const ulong expectedNumber = 8;
            const ushort expectedIndex = 0;

            // Act
            var subject = new Factor(expectedNumber);

            // Assert
            subject.Number.Should().Be(expectedNumber);
            subject.NextIndex.Should().Be(expectedIndex);
            subject.NextValue.Should().Be(expectedNumber);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(1)]
        public void Constructor_FactorLesserOrEqualThan1_ArgumentException(ushort factor)
        {
            // Arrange
            Factor instantiation() => new Factor(factor);

            // Assert
            Assert.Throws<ArgumentException>("factor", instantiation);
        }

        [Fact]
        public void Implicit_InstantiatesNewFactor()
        {
            // Arrange
            const ulong expectedNumber = 12;
            const ushort expectedIndex = 0;

            // Act
            Factor subject = expectedNumber;

            // Assert
            subject.Number.Should().Be(expectedNumber);
            subject.NextIndex.Should().Be(expectedIndex);
            subject.NextValue.Should().Be(expectedNumber);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(1)]
        public void Implicit_FactorLesserOrEqualThan1_ArgumentException(ushort factor)
        {
            // Arrange
            Factor instantiation() => factor;

            // Assert
            Assert.Throws<ArgumentException>("factor", instantiation);
        }

        [Fact]
        public void ToFactor_InstantiatesNewFactor()
        {
            // Arrange
            const ulong expectedNumber = 12;
            const ushort expectedIndex = 0;

            // Act
            var subject = Factor.ToFactor(expectedNumber);

            // Assert
            subject.Number.Should().Be(expectedNumber);
            subject.NextIndex.Should().Be(expectedIndex);
            subject.NextValue.Should().Be(expectedNumber);
        }

        [Theory]
        [InlineData(0)]
        [InlineData(1)]
        public void ToFactor_FactorLesserOrEqualThan1_ArgumentException(ushort factor)
        {
            // Arrange
            Factor instantiation() => Factor.ToFactor(factor);

            // Assert
            Assert.Throws<ArgumentException>("factor", instantiation);
        }
        #endregion

        #region CompareTo
        [Theory]
        [MemberData(nameof(CompareTo_TestData))]
        public void CompareTo_ReturnsExpected(Factor subject, Factor factorB, ComparisonResult expectedResult)
        {
            // Act
            var result = subject.CompareTo(factorB);

            // Assert
            switch (expectedResult)
            {
                case ComparisonResult.Lesser:
                    result.Should().BeLessThan(0);
                    break;
                case ComparisonResult.Equal:
                    result.Should().Be(0);
                    break;
                case ComparisonResult.Greater:
                    result.Should().BeGreaterThan(0);
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(expectedResult), $"Unexpected value: \"{expectedResult}\"");
            }
        }
        public static IEnumerable<object[]> CompareTo_TestData()
        {
            var testSuite = new (object, object, ComparisonResult)[]
            {
                (new Factor(2), new Factor(2), ComparisonResult.Equal),
                (new Factor(2), new Factor(3), ComparisonResult.Lesser),
                (new Factor(3), new Factor(2), ComparisonResult.Greater),
                (new Factor(3), null, ComparisonResult.Greater),
            };
            foreach (var sample in testSuite)
            {
                yield return new object[]
                {
                    sample.Item1,
                    sample.Item2,
                    sample.Item3
                };
            }
        }

        public enum ComparisonResult
        {
            Lesser = -1,
            Equal = 0,
            Greater = 1,
        }
        #endregion
    }
}
