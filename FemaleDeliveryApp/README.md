# Female Delivery Multi-Platform MVP (SwiftUI-first)

This folder contains a SwiftUI MVP baseline for **女生送货 / Female Delivery** and shows how to prepare for multiple storefront platforms.

## Implemented requirements
- App name: Female Delivery (中文：女生送货)
- First launch countries: China + United States
- Business type: delivery service
- Online payment flow (mock service)
- Women-only access enforcement in registration flow
- Multi-platform configuration support (iOS / Android / Web)

## What changed for multi-platform listing
- Added `Config/PlatformConfig.swift`:
  - `AppPlatform`: iOS / Android / Web
  - `PlatformConfig`: per-platform country and payment capabilities
  - `PlatformRegistry`: centralized release matrix
- Registration now includes target platform selection and validates country/gender on that platform.
- Order creation now derives available payment providers by platform+country.

## Project structure
- `FemaleDeliveryAppApp.swift`: app entry
- `Config/PlatformConfig.swift`: platform release + payment matrix
- `Models/AppModels.swift`: country, gender, user, order models
- `Services/EligibilityService.swift`: women-only and platform-country eligibility checks
- `Services/PaymentService.swift`: async payment mock with provider-based reference
- `ViewModels/AuthViewModel.swift`: registration/auth state
- `ViewModels/OrderViewModel.swift`: order + payment state
- `Views/*.swift`: sign-up, home, create order pages

## Production recommendations
- iOS: keep SwiftUI and integrate Apple Pay + Stripe/Alipay/WeChat based on country.
- Android: build parity screens in Kotlin + Jetpack Compose and connect to the same backend contracts.
- Web: build merchant/user console in React/Vue and reuse platform config from backend APIs.
- Move `PlatformRegistry` into backend feature flags so rollout can be changed without app release.
