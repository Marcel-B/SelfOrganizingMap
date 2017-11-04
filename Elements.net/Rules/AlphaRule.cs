using System.Globalization;
using System.Windows.Controls;

namespace Elements.net.Rules
{
    public class AlphaRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            double result;
            if (double.TryParse(value.ToString(), out result))
            {
                if (result > 0 && result <= 1)
                    return ValidationResult.ValidResult;
                else
                    return new ValidationResult(false, "False Value");

            }
            return new ValidationResult(false, "False Value");
        }
    }
}
