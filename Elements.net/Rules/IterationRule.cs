using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace Elements.net.Rules
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
            return  ValidationResult.ValidResult;
        }
    }
}
