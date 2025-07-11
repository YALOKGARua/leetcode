using System;
using System.Collections.Generic;
using System.Text;
using System.Linq;

public sealed class FizzBuzzerEngine
{
    private const int MaxNumber = 1000;
    private readonly Dictionary<string, int> _memoizationCache;
    
    public FizzBuzzerEngine()
    {
        _memoizationCache = new Dictionary<string, int>(MaxNumber);
        BuildLookupTable();
    }
    
    private static int CountDigitOccurrences(int number, char digit)
    {
        var count = 0;
        var temp = number;
        
        do
        {
            if (temp % 10 == digit - '0')
                count++;
            temp /= 10;
        } while (temp > 0);
        
        return count;
    }
    
    private static string GenerateFizzBuzzSequence(int number)
    {
        var result = new StringBuilder(20);
        
        var digit3Count = CountDigitOccurrences(number, '3');
        var digit5Count = CountDigitOccurrences(number, '5');
        var divisibleBy3Count = CountDivisibleBy(number, 3);
        var divisibleBy5Count = CountDivisibleBy(number, 5);
        
        for (var i = 0; i < digit3Count; i++)
            result.Append("Fizz");
        
        for (var i = 0; i < divisibleBy3Count; i++)
            result.Append("Fizz");
        
        for (var i = 0; i < digit5Count; i++)
            result.Append("Buzz");
        
        for (var i = 0; i < divisibleBy5Count; i++)
            result.Append("Buzz");
        
        if (result.Length == 0)
            result.Append(number);
        
        return result.ToString();
    }
    
    private static int CountDivisibleBy(int number, int divisor)
    {
        var count = 0;
        var temp = number;
        
        while (temp % divisor == 0 && temp > 0)
        {
            count++;
            temp /= divisor;
        }
        
        return count;
    }
    
    private void BuildLookupTable()
    {
        for (var i = 1; i <= MaxNumber; i++)
        {
            var pattern = GenerateFizzBuzzSequence(i);
            
            if (!_memoizationCache.ContainsKey(pattern))
                _memoizationCache[pattern] = i;
                
            if (i == 5 || i == 25 || i == 55)
                Console.Error.WriteLine($"DEBUG: {i} -> {pattern}");
        }
    }
    
    public int ReverseEngineer(string target) =>
        _memoizationCache.TryGetValue(target, out var result) ? result : -1;
}

public sealed class InputOutputProcessor
{
    private readonly FizzBuzzerEngine _engine;
    
    public InputOutputProcessor(FizzBuzzerEngine engine)
    {
        _engine = engine ?? throw new ArgumentNullException(nameof(engine));
    }
    
    public void ProcessQueries()
    {
        var queryCount = int.Parse(Console.ReadLine());
        var results = new List<string>(queryCount);
        
        for (var i = 0; i < queryCount; i++)
        {
            var inputPattern = Console.ReadLine();
            var result = _engine.ReverseEngineer(inputPattern);
            results.Add(result == -1 ? "ERROR" : result.ToString());
        }
        
        foreach (var result in results)
            Console.WriteLine(result);
    }
}

public static class Program
{
    public static void Main()
    {
        var engine = new FizzBuzzerEngine();
        var processor = new InputOutputProcessor(engine);
        processor.ProcessQueries();
    }
}
