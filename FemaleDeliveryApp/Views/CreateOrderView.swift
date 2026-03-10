import SwiftUI

struct CreateOrderView: View {
    @EnvironmentObject private var authViewModel: AuthViewModel
    @EnvironmentObject private var orderViewModel: OrderViewModel

    @State private var pickupAddress = ""
    @State private var dropoffAddress = ""
    @State private var packageDescription = "Documents"
    @State private var note = ""
    @State private var distanceKM = "5"
    @State private var cardLast4 = ""
    @State private var selectedPaymentProvider: PaymentProvider = .stripe

    var country: SupportedCountry {
        authViewModel.currentUser?.country ?? .china
    }

    var platform: AppPlatform {
        authViewModel.currentUser?.platform ?? .ios
    }

    var providers: [PaymentProvider] {
        orderViewModel.availablePaymentProviders(platform: platform, country: country)
    }

    var estimatedFee: Decimal {
        orderViewModel.estimateFee(country: country, distanceKM: Double(distanceKM) ?? 0)
    }

    var body: some View {
        Form {
            Section("Order") {
                TextField("Pickup address", text: $pickupAddress)
                TextField("Dropoff address", text: $dropoffAddress)
                TextField("Package description", text: $packageDescription)
                TextField("Note", text: $note)
                TextField("Distance (KM)", text: $distanceKM)
                    .keyboardType(.decimalPad)

                Text("Estimated fee: $\(estimatedFee.description)")
            }

            Section("Online Payment") {
                Picker("Provider", selection: $selectedPaymentProvider) {
                    ForEach(providers, id: \.rawValue) { provider in
                        Text(provider.rawValue).tag(provider)
                    }
                }
                .onAppear {
                    if let first = providers.first {
                        selectedPaymentProvider = first
                    }
                }

                TextField("Card last 4 digits", text: $cardLast4)
                    .keyboardType(.numberPad)

                Button("Submit order & Pay") {
                    orderViewModel.createOrder(
                        pickupAddress: pickupAddress,
                        dropoffAddress: dropoffAddress,
                        packageDescription: packageDescription,
                        note: note,
                        country: country,
                        platform: platform,
                        distanceKM: Double(distanceKM) ?? 0,
                        paymentProvider: selectedPaymentProvider
                    )

                    Task {
                        await orderViewModel.payLatestOrder(cardLast4: cardLast4)
                    }
                }
                .disabled(pickupAddress.isEmpty || dropoffAddress.isEmpty || cardLast4.count != 4 || providers.isEmpty)

                if let status = orderViewModel.paymentStatusMessage {
                    Text(status)
                        .foregroundStyle(status.contains("successful") ? .green : .red)
                }
            }
        }
        .navigationTitle("Delivery Order")
    }
}
