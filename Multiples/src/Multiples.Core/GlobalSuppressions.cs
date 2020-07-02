// This file is used by Code Analysis to maintain SuppressMessage
// attributes that are applied to this project.
// Project-level suppressions either have no target or are given
// a specific target and scoped to a namespace, type, member, etc.

using System.Diagnostics.CodeAnalysis;
using System.Runtime.CompilerServices;

[assembly: InternalsVisibleTo("Multiples.Core.Tests")]

[assembly: SuppressMessage("Design", "CA1036:Override methods on comparable types", Justification = "Not Required at this moment", Scope = "type", Target = "~T:SmokingGunInc.Multiples.Factor")]
[assembly: SuppressMessage("Globalization", "CA1303:Do not pass literals as localized parameters", Justification = "Exceptions Message", Scope = "type", Target = "~T:SmokingGunInc.Multiples.LinearMultiplesService")]