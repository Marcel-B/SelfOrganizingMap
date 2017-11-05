using System.Globalization;
using System.Windows.Controls;

namespace com_b_velop.Rules
{
    public class IterationRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            long result;
            if (long.TryParse(value.ToString(), out result))
            {
                if (result > 0)
                    return ValidationResult.ValidResult;
                return new ValidationResult(false, "Der Wert muss positiv sein");
            }
            return new ValidationResult(false, "Der Wert muss positiv sein");
        }
    }
}
