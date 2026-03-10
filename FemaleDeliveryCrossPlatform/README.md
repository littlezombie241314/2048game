# Female Delivery Cross-Platform (Flutter)

This is a **single codebase** Flutter app intended for direct deployment to:
- iOS App Store
- Android Google Play
- Web hosting (for web launch)

## Why this version
The previous Swift-only code could not be directly published to Android/Web. This Flutter implementation provides one shared app codebase for all three platforms.

## Included capabilities
- Women-only access rule
- Launch countries: China + United States
- Platform-aware payment methods
- Delivery order flow
- Mock online payment flow
- Girl-friendly UI style (soft pink palette, rounded cards, warm visual hierarchy)
- Windows-friendly interactions (hover feedback, desktop two-column layout, larger click targets)

## Run locally
```bash
flutter pub get
flutter run -d chrome   # Web
flutter run -d ios      # iOS (macOS + Xcode required)
flutter run -d android  # Android emulator/device required
```

## Build for stores
```bash
flutter build ios
flutter build appbundle
flutter build web
```

## Notes
- Replace `mockPay` with real payment SDK integrations by platform/country.
- Move `PlatformRegistry` data to backend feature flags for runtime rollout control.
