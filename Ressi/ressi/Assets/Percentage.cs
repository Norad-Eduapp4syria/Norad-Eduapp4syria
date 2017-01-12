using System;

[Serializable]
public class Percentage
{
    protected bool Equals(Percentage other)
    {
        return Value == other.Value;
    }

    public override bool Equals(object obj)
    {
        if (ReferenceEquals(null, obj)) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != this.GetType()) return false;
        return Equals((Percentage) obj);
    }

    public override int GetHashCode()
    {
        return Value;
    }

    public static bool operator ==(Percentage left, Percentage right)
    {
        return Equals(left, right);
    }

    public static bool operator !=(Percentage left, Percentage right)
    {
        return !Equals(left, right);
    }

    public static bool operator >(Percentage left, Percentage right)
    {
        return left.Value > right.Value;
    }

    public static bool operator <(Percentage left, Percentage right)
    {
        return left.Value < right.Value;
    }

    public static bool operator >=(Percentage left, Percentage right)
    {
        return left.Value >= right.Value;
    }

    public static bool operator <=(Percentage left, Percentage right)
    {
        return left.Value <= right.Value;
    }

    public Percentage(int value)
    {
        if(value < 0) throw new ArgumentException("Must be >= 0", "value");
        if (value > 100) throw new ArgumentException("Must be <= 100", "value");

        Value = value;
    }

    public int Value { get; private set; }

    public static readonly Percentage OneHundred = new Percentage(100);
    public static readonly Percentage Zero = new Percentage(0);

    public Percentage Add(int value, bool clampAllowedRange = true)
    {
        var newValue = Value + value;

        if (clampAllowedRange  && newValue < 0) newValue = 0;
        if (clampAllowedRange  && newValue > 100) newValue = 100;

        return new Percentage(newValue);
    }

    public override string ToString()
    {
        return Value + "%";
    }
}