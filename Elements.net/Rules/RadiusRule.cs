using System.Globalization;
using System.Windows.Controls;

namespace com_b_velop.Rules
{
    public class RadiusRule : ValidationRule
    {
        public override ValidationResult Validate(object value, CultureInfo cultureInfo)
        {
            int result;
            if (int.TryParse(value.ToString(), out result))
            {
                if(result >= 0)
                    return ValidationResult.ValidResult;
                return new ValidationResult(false, "Negative Werte sind unzulässig");
            }
            return new ValidationResult(false, "Negative Werte sind unzulässig");
        }
    }
}
