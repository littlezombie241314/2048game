import 'package:flutter_test/flutter_test.dart';
import 'package:female_delivery_cross_platform/main.dart';

void main() {
  test('female user in CN on iOS passes', () {
    final result = validateAccess(
      gender: Gender.female,
      country: SupportedCountry.china,
      platform: AppPlatform.ios,
    );
    expect(result, isNull);
  });

  test('male user blocked', () {
    final result = validateAccess(
      gender: Gender.male,
      country: SupportedCountry.us,
      platform: AppPlatform.android,
    );
    expect(result, isNotNull);
  });

  test('payment providers available for web us', () {
    final providers = PlatformRegistry.of(AppPlatform.web).paymentProviders(SupportedCountry.us);
    expect(providers, contains(PaymentProvider.stripe));
  });

  test('windows platform config exists', () {
    final providers = PlatformRegistry.of(AppPlatform.windows).paymentProviders(SupportedCountry.china);
    expect(providers, isNotEmpty);
  });
}
