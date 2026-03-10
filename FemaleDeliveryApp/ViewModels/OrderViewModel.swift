import Foundation

@MainActor
final class OrderViewModel: ObservableObject {
    @Published var orders: [DeliveryOrder] = []
    @Published var paymentStatusMessage: String?

    private let paymentService = PaymentService()

    func availablePaymentProviders(platform: AppPlatform, country: SupportedCountry) -> [PaymentProvider] {
        PlatformRegistry.config(for: platform).paymentProviders(for: country)
    }

    func estimateFee(country: SupportedCountry, distanceKM: Double) -> Decimal {
        let base: Decimal = country == .china ? 3.5 : 6.0
        let distancePart = Decimal(distanceKM) * Decimal(string: "0.8")!
        return base + distancePart
    }

    func createOrder(
        pickupAddress: String,
        dropoffAddress: String,
        packageDescription: String,
        note: String,
        country: SupportedCountry,
        platform: AppPlatform,
        distanceKM: Double,
        paymentProvider: PaymentProvider
    ) {
        let order = DeliveryOrder(
            pickupAddress: pickupAddress,
            dropoffAddress: dropoffAddress,
            packageDescription: packageDescription,
            note: note,
            country: country,
            platform: platform,
            estimatedFeeUSD: estimateFee(country: country, distanceKM: distanceKM),
            paymentProvider: paymentProvider,
            isPaid: false
        )
        orders.insert(order, at: 0)
    }

    func payLatestOrder(cardLast4: String) async {
        guard !orders.isEmpty else {
            paymentStatusMessage = "No order found."
            return
        }

        do {
            let reference = try await paymentService.pay(order: orders[0], cardLast4: cardLast4)
            orders[0].isPaid = true
            paymentStatusMessage = "Payment successful: \(reference)"
        } catch {
            paymentStatusMessage = error.localizedDescription
        }
    }
}
